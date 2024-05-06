import os
from lxml import etree
from collections import OrderedDict

class TemplateXML :
    def __init__(self, path) :
        parser = etree.XMLParser(remove_blank_text=True)
        self.doc = etree.parse(path,parser)
        self.name = os.path.basename(path)
        self.folder = os.path.realpath(os.path.dirname(path))
    def descriptor_containing_slcp(self, path) :
        target = os.path.relpath(os.path.realpath(path),self.folder)
        for f in self.doc.iter('descriptors') :
            for g in f.iter('properties') :
                key = g.attrib.get('key')
                if None == key :
                    continue
                if 'template.projectFilePaths' != key :
                    continue
                path = g.attrib.get('value')
                if None == path :
                    raise RuntimeError
                if target == path :
                    return f
        return None
    def add_descriptor(self, descriptor, app) :
        orderedDict = OrderedDict([("name",app['project_name']),("label",app['label']),("description",app['description'])])
        descriptors = etree.SubElement(self.doc.getroot(), 'descriptors', orderedDict)
        for p in descriptor.iter('properties') :
            key = p.attrib.get('key')
            value = p.attrib.get('value')
            properties = etree.SubElement(descriptors, 'properties',
                                          key=key, value=value)
    def write(self,path) :
        self.doc.write(path, pretty_print=True, xml_declaration=True)#,encoding='utf-8')
        return
        text = etree.tostring(self.doc, pretty_print=True, xml_declaration=True,encoding='utf-8').decode("utf-8")
        fh = open(path,'w')
        fh.write(text)
        fh.close()
        
def set_property(descriptor, property, value) :
    if etree._Element != type(descriptor) :
        raise ValueError(type(descriptor))
    found = False
    for p in descriptor.iter() :
        key = p.attrib.get('key')
        if None == key :
            continue
        if property == key :
            p.attrib['value'] = value
            return
    properties = etree.SubElement(descriptor, 'properties',
                                  key=property, value=value)
    
def set_slcp(d, slcp) :
    set_property(d, 'template.projectFilePaths', slcp)

def set_default_name(d,name) :
    set_property(d, 'defaultName', name)

def set_quality(d, quality) :
    set_property(d, 'quality', quality.upper())
