import os
import yaml

class Project :
    class File :
        def __init__(self, name, path) :
            self.name = name
            self.path = path
            self.folder = None
            self.content = None
        def get_relpath(self,from_project_root=False) :
            result = []
            obj = self
            while None != obj :
                result = [obj.name]+result
                obj = obj.folder
            return '/'.join(result[int(from_project_root):])
    class Folder :
        def __init__(self, name, path=None) :
            self.name = name
            self.path = path
            self.folder = None
            self.content = {}
        def add(self,name,obj) :
            self.content[obj.name] = obj
            obj.folder = self
    def __init__(self,path) :
        self.name = os.path.basename(path)
        self.slcp = []
        self.root = self.recurse(path,self.name)
        self.get_paths()
    def set_name(self, name) :
        self.name = name
        self.root.name = name
    def recurse(self,path,name) :
        dir = self.Folder(name,path)
        for entry in os.listdir(path) :
            entryPath = path+'/'+entry
            if os.path.isdir(entryPath) :
                dir.add(entry,self.recurse(entryPath,entry))
            elif os.path.isfile(entryPath) :
                file = self.File(entry,entryPath)
                if len(entry) > 5 and '.slcp' == entry[-5:] :
                    file.content = yaml.load(open(entryPath,'r'), Loader=yaml.SafeLoader)
                    self.slcp.append(file)
                dir.add(entry,file)
        return dir
    def regular_files(self,root=None) :
        if None == root :
            return self.regular_files(self.root)
        local= []
        for name in root.content :
            entry = root.content[name]
            if type(entry) == self.File :
                if len(entry.name) > 5 and '.slcp' == entry.name[-5:] :
                    continue
                local.append(entry)
            elif type(entry) == self.Folder :
                local += self.regular_files(entry)
            else :
                raise RuntimeError(type(entry))
        return local
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
                self.recursive_copy(npath,obj)
    def get_paths(self, object=None,key=None) :
        if None == object :
            self.paths = {}
            for slcp in self.slcp :
                self.paths[slcp] = self.get_paths(slcp.content)
            return
        total = {}
        returns = []
        object_type = type(object)
        if dict == object_type :
            for key in object :
                if 'ui_hints' == key : continue
                value = object[key]
                if 'path' == key :
                    if None != total.get(value) :
                        raise RuntimeError(value)
                    total[value] = key
                else :
                    db = self.get_paths(value,key)
                    for subkey in db :
                        value = db[subkey]
                        if None != total.get(value) :
                            raise RuntimeError(value)
                        total[subkey] = key
        elif list == object_type :
            for subobject in object :
                db = self.get_paths(subobject,key)
                for subkey in db :
                    value = db[subkey]
                    if None != total.get(value) :
                        raise RuntimeError(value)
                    total[subkey] = key
        return total
    
