find . -name "*.cpp" -exec g++ -MM -I./  {} \; > .vscode/all_deps.txt
cd .vscode
python3 deps.py
dot -Tpng deps_graph.dot -o graph.png
rm all_deps.txt
rm deps_graph.dot
cd ..
