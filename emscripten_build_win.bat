@echo off

docker build . -t build_emscripten
docker run -v %CD%:/app build_emscripten
