import argparse
import os
import yaml
from project import Project

parser = argparse.ArgumentParser()
parser.add_argument('--name',required=True,help='Project name')
parser.add_argument('--studio',required=True,help='Live Studio project to copy from')
parser.add_argument('--debug',action='store_true')
parser.add_argument('--write',action='store_true')
args = parser.parse_args()

if args.debug :
    print('args:',args)

if not os.path.exists('templates.xml') :
    raise RuntimeError('Run this script from root of repo')

for ch in args.name :
    if not ch.isalnum() and '_' != ch :
        raise RuntimeError('Invalid characters in name (%s)'%(ch))

if not os.path.exists(args.name) :
    raise RuntimeError('folder %s does not exist'%(args.name))
if not os.path.isdir(args.name) :
    raise RuntimeError('%s is not a folder'%(args.name))

if not os.path.exists(args.studio) :
    raise RuntimeError('Copy from Studio folder %s does not exist'%(args.studio))
if not os.path.isdir(args.studio) :
    raise RuntimeError('%s is not a folder'%(args.studio))

project = Project(args.name)
#print([x.get_relpath() for x in project.regular_files()])

changes = False
for file in project.regular_files() :
    studio_filename = args.studio+'/'+file.get_relpath(from_project_root=True)
    if not os.path.exists(studio_filename) :
        directory = None
        for slcp in project.slcp :
            config = slcp.content.get('config_file')
            if None == config : continue
            for entry in config :
                if entry.get('path') != file.name : continue
                directory = entry.get('directory')
                if None == directory :
                    directory = config
                else :
                    directory = 'config/'+directory
        if None == directory :
            raise RuntimeError(studio_filename)
        studio_filename = args.studio+'/'+directory+'/'+file.name
    binary_mode = False
    for slcp in project.slcp :
        if 'other_file' == project.paths[slcp][file.get_relpath(from_project_root=True)] :
            binary_mode = True
    if binary_mode :
        a = open(file.get_relpath(),'rb').read()
        b = open(studio_filename,'rb').read()
    else :
        a = open(file.get_relpath(),'r').read()
        b = open(studio_filename,'r').read().replace('\r\n','\n')
    if a == b :
        continue
    changes = True
    if b.find('\r') >= 0 : print('Has CR')
    if args.write :
        print('Updating %s'%(file.get_relpath()))
        if binary_mode :
            open(file.get_relpath(),'wb').write(b)
        else :
            open(file.get_relpath(),'w').write(b)
    elif args.debug :
        command = 'diff -w %s %s'%(file.get_relpath(),studio_filename)
        os.system(command)
        print('%s is not up to date'%(file.get_relpath()))
        
if changes and not args.write :
    print('No modifications made, use --write to force')
