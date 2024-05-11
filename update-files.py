import argparse
import os
import template_process as TP
import yaml
from project import Project

parser = argparse.ArgumentParser()
parser.add_argument('--name',required=True,help='Project name')
parser.add_argument('--studio',required=True,help='Live Studio project to copy from')
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

for file in project.regular_files() :
    studio_filename = args.studio+'/'+file.name
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
            raise RuntimeError
        studio_filename = args.studio+'/'+directory+'/'+file.name
    a = open(file.get_relpath(),'r').read()
    b = open(studio_filename,'r').read()
    if a == b :
        continue
    print(studio_filename)
