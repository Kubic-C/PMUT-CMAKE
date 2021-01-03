cd build
echo "@-! CMAKE GENERATING PROJECT"
cmake .. -G Ninja

echo "@-! NINJA BUILDING APP"
ninja

echo "@-! RUNNING APP"
./projects/pmut/pmut

echo "@-! APP FINISHED"