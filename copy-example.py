import argparse
import os
import template_process as TP
import yaml

parser = argparse.ArgumentParser()
parser.add_argument('--name',required=True,help='Project name')
parser.add_argument('--source',required=True,help='Folder to be copied')
parser.add_argument('--quality',default='experimental',help='Quality of project ... leave default')
parser.add_argument('--description',required=True,help='Longer description of project')
parser.add_argument('--label',required=True,help='Project short description')
parser.add_argument('--component',help='Comma delimited list of components')
parser.add_argument('--configuration',help='Comma delimited list of configurations')
parser.add_argument('--define',help='Comma delimited list of defines (X or X=Y)')
parser.add_argument('--vcom',action='store_true',help='Enable VCOM without additional drivers')
parser.add_argument('--vcom-printf',action='store_true',help='Enable VCOM using Tiny Printf')
parser.add_argument('--vcom-log',action='store_true',help='Enable VCOM using app_log')
parser.add_argument('--debug',action='store_true')
args = parser.parse_args()

if args.debug :
    print('args:',args)

if not os.path.exists('templates.xml') :
    raise RuntimeError('Run this script from root of repo')
target_template = TP.TemplateXML('templates.xml')

for ch in args.name :
    if not ch.isalnum() and '_' != ch :
        raise RuntimeError('Invalid characters in name (%s)'%(ch))
    
try :
    sb = os.stat(args.name)
    raise RuntimeError('folder %s exists'%(args.name))
except FileNotFoundError :
    pass

if not os.path.exists(args.source) :
    raise RuntimeError('Source folder %s does not exist'%(args.source))
if not os.path.isdir(args.source) :
    raise RuntimeError('%s is not a folder'%(args.source))

class Project :
    class File :
        def __init__(self, name, path=None) :
            self.name = name
            self.path = path
            self.folder = None
            self.content = None
        def get_relpath(self) :
            result = []
            obj = self
            while None != obj :
                print(obj.name)
                result = [obj.name]+result
                obj = obj.folder
            return '/'.join(result)
    class Folder :
        def __init__(self, name, path=None) :
            self.name = name
            self.path = path
            self.folder = None
            self.content = {}
        def add(self,name,obj) :
            self.content[obj.name] = obj
            obj.folder = self
    def __init__(self,name,path) :
        self.name = args.name
        self.slcp = []
        self.root = self.recurse(path,name)
    def recurse(self,path,name) :
        dir = self.Folder(name,path)
        for entry in os.listdir(path) :
            entryPath = path+'/'+entry
            if os.path.isdir(entryPath) :
                dir.add(self.recurse(entryPath))
            elif os.path.isfile(entryPath) :
                file = self.File(entry,entryPath)
                if len(entry) > 5 and entry.find('.slcp') == (len(entry) - 5) :
                    self.slcp.append(file)
                dir.add(entry,file)
        return dir
    def recursive_copy(self, path, folder) :
        os.mkdir(path)
        for name in folder.content :
            obj = folder.content[name]
            npath = path + '/' + obj.name
            if self.File == type(obj) :
                source = obj.path
                dest = npath
                if None == obj.content :
                    open(dest,'wb').write(open(source,'rb').read())
                else :
                    yaml.dump(obj.content,
                              open(dest,'w'),
                              default_flow_style=False)
                print('copy %s %s'%(source,dest))
            elif self.Folder == type(obj) :
                recursive_copy(npath,obj)
        
project = Project(args.name,args.source)

for slcp in project.slcp :
    if None != target_template.descriptor_containing_slcp(slcp.path) :
        raise RuntimeError('template.xml already contains %s'%(slcp.name))

descriptors = {}
done = False
path = os.path.realpath(args.source)
while not done :
    previous = path
    path = os.path.realpath(previous+'/..')
    if path == previous :
        names = ', '.join([x.name for x in project.slcp])
        raise RuntimeError('Hit rock bottom searching for template containing %s')
    for entry in os.listdir(path) :
        pathname = path+'/'+entry
        if os.path.isfile(pathname) and entry.find('templates') > 0 and '.xml' == entry[-4:] :
            template = TP.TemplateXML(pathname)
            for slcp in project.slcp :
                descriptor = template.descriptor_containing_slcp(slcp.path)
                if None == descriptor :
                    continue
                if None != descriptors.get(slcp) :
                    raise RuntimeError('Multiple matches for %s'%(slcp.name))
                descriptors[slcp] = descriptor
                slcp.descriptor = descriptor
                print('found %s in %s'%(slcp.name,pathname))
    done = True
    for slcp in project.slcp :
        if None == descriptors.get(slcp) :
            done = False

def append(db,label,value) :
    if None == db.get(label) :
        db[label] = []
    db[label].append(value)

if 1 == len(project.slcp) :
    project.slcp[0].name = args.name + '.slcp'
    
for slcp in project.slcp :
    db = yaml.load(open(slcp.path,'r'), Loader=yaml.SafeLoader)
    db['project_name'] = args.name
    db['quality'] = args.quality
    db['label'] = args.label
    db['description'] = args.description
    if None == db.get('component') :
        db['component'] = []
    if None != args.component :
        for component in args.component.split(',') :
            tokens = component.split(':')
            if len(tokens) > 1 :
                instances = tokens[1].split('|')
                db['component'].append({'instance':[','.join(instances)], 'id':tokens[0]})
            else :
                db['component'].append({'id':component})
    if None != args.configuration :
        for config in args.configuration.split(',') :
            tokens = config.split('=')
            db['configuration'].append({'name':tokens[0], 'value':tokens[1]})
    if None != args.define :
        for define in args.define.split(',') :
            tokens = define.split('=')
            if len(tokens) > 1 :
                db['define'].append({'name':tokens[0], 'value':tokens[1]})
            else :
                db['configuration'].append({'name':tokens[0]})
    if args.vcom or args.vcom_printf or args.vcom_app_log :
        append(db,'component',{'instance':['vcom'],'id':'iostream_usart'})
        append(db,'configuration',{'name':'SL_IOSTREAM_USART_VCOM_CONVERT_BY_DEFAULT_LF_TO_CRLF','value':'1'})
        append(db,'configuration',{'name':'SL_IOSTREAM_USART_VCOM_RESTRICT_ENERGY_MODE_TO_ALLOW_RECEPTION','value':'1'})
        append(db,'configuration',{'name':'SL_BOARD_ENABLE_VCOM','value':'1'})
    if args.vcom_log :
        append(db,'component',{'id':'app_log'})
    if args.vcom_printf :
        append(db,'component',{'id':'printf'})
    slcp.content = db
    target_template.add_descriptor(slcp.descriptor, db, slcp.get_relpath())
    
target_template.write('/tmp/delete.xml')
project.recursive_copy(project.root.name,project.root)
