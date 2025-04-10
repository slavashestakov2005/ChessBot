import os
from collections import defaultdict


dependencies = defaultdict(list)


dirs =[".", "board", "bot", "figures", "settings", "tests", "ui"]
# colors = {'.': 'blue', 'board': 'red', 'bot': 'green', 'figures': 'yellow', 'settings': 'magenta', 'tests': 'cyan', 'ui': 'orange'}
# colors = {'.': '#6A8A82', 'board': '#D4A5A5', 'bot': '#7C9EB2', 'figures': '#B2C9AB', 'settings': '#C4B6B6', 'tests': '#E6C229', 'ui': '#8A6E64'}
colors = {'settings': '#FFD166', 'board': '#6B8CDD', 'bot': '#77DD77', 'figures': '#FF6B6B', 'tests': '#D4A5D4', '.': '#7FDBFF', 'ui': '#FFAA5E'}
names = {'.': 'Главные файлы', 'board': 'Доска', 'bot': 'Бот', 'figures': 'Фигуры', 'settings': 'Настройки', 'tests': 'Тесты', 'ui': 'Интерфейс'}
cpp_files = {}
for cur in dirs:
    for file in os.scandir(cur):
        if '.cpp' in file.name:
            cpp_files[file.name.replace('.cpp', '.o')] = cur + '/' + file.name.rsplit('.')[0]


with open("all_deps.txt", "r") as f:
    target = None
    clean_deps = None
    for line in f:
        line = line.strip()
        if not line:
            continue
        
        if ':' in line:
            parts = line.split(":")
            if target is not None:
                dependencies[target] = list(clean_deps)
            target = cpp_files[parts[0].strip()]
            clean_deps = set()
            deps = parts[1].strip().split()
        else:
            deps = line.strip().split()
        
        for dep in deps:
            if "/usr/include/" in dep:
                continue
            if dep == '\\':
                continue
            dep = dep.rsplit('.')[0]
            if '/' not in dep:
                dep = './' + dep
            clean_deps.add(dep)
        
    if target is not None:
        dependencies[target] = list(clean_deps)


with open("deps_graph.dot", "w") as f:
    f.write("digraph Dependencies {\n")
    f.write('    node [fontname="Arial", shape=oval];\n')
    
    all_files = set()
    for target, deps in dependencies.items():
        all_files.add(target)
        for dep in deps:
            all_files.add(dep)

    for cur in dirs:
        f.write(f'    "__{cur}__" [style=filled, color="{colors[cur]}", label="{names[cur]}"];\n')

    for target in all_files:
        folder = target.split('/')[0]
        color = colors[folder]
        filename = target.split('/')[1]
        f.write(f'    "{target}" [style=filled, color="{color}", label={filename}];\n')

    # for cur in dirs:
    #     f.write(f'    "__{cur}__" [style=filled, color="{colors[cur]}", label="{names[cur]}"];\n')

    for target, deps in dependencies.items():
        for dep in deps:
            if dep != target:
                f.write(f'    "{target}" -> "{dep}";\n')
    
    f.write("}\n")

print("Граф сохранён в deps_graph.dot")
