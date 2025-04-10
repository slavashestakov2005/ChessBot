find . -name "*.cpp" -exec g++ -MM -I./  {} \; > .vscode/all_deps.txt
python3 .vscode/deps.py
cd .vscode
dot -Tpng deps_graph.dot -o graph.png
rm all_deps.txt
rm deps_graph.dot
cd ..
