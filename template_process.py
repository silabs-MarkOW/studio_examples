import os
from lxml import etree
from collections import OrderedDict

class TemplateXML :
    def __init__(self, path) :
        print('TemplateXML:loading %s'%(path))
        parser = etree.XMLParser(remove_blank_text=True)
        self.doc = etree.parse(path,parser)
        self.name = os.path.basename(path)
        self.folder = os.path.realpath(os.path.dirname(path))
    def descriptor_containing_slcp(self, path) :
        target = os.path.relpath(os.path.realpath(path),self.folder)
        seeking = 'projectFilePaths'
        for f in self.doc.iter('descriptors') :
            for g in f.iter('properties') :
                key = g.attrib.get('key')
                if None == key :
                    continue
                if 'type' == key :
                    value = g.attrib.get('value')
                    if 'template' == value :
                        seeking = 'template.projectFilePaths'
            for g in f.iter('properties') :
                key = g.attrib.get('key')
                if None == key :
                    continue
                if seeking != key :
                    continue
                path = g.attrib.get('value')
                if None == path :
                    raise RuntimeError
                if target == path :
                    return f
        return None
    def add_descriptor(self, descriptor, app, slcp) :
        orderedDict = OrderedDict([("name",app['project_name']),("label",app['label']),("description",app['description'])])
        descriptors = etree.SubElement(self.doc.getroot(), 'descriptors', orderedDict)
        got_quality = False
        for p in descriptor.iter('properties') :
            key = p.attrib.get('key')
            value = p.attrib.get('value')
            if 'type' == key : continue
            if 'defaultName' == key : continue
            if 'template.projectFilePaths' == key :
                key = 'projectFilePaths'
                value = slcp
            if 'projectFilePaths' == key :
                value = slcp
            if 'quality' == key :
                value = app['quality'].upper()
                got_quality = True
            properties = etree.SubElement(descriptors, 'properties',
                                          key=key, value=value)
        if not got_quality :
            properties = etree.SubElement(descriptors, 'properties',
                                          key='quality', value=app['quality'].upper())
    def write(self,path) :
        self.doc.write(path, pretty_print=True, xml_declaration=True)#,encoding='utf-8')
        return
        text = etree.tostring(self.doc, pretty_print=True, xml_declaration=True,encoding='utf-8').decode("utf-8")
        fh = open(path,'w')
        fh.write(text)
        fh.close()
