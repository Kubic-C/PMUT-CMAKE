mkdir build
mkdir release
cd build

echo "@-! CMAKE GENERATING PROJECT"
cmake .. -G Ninja

echo "@-! NINJA BUILDING APP"
ninja

echo "@-! COPYING DEPENDENCIES"
cd ..
cp  -v -r ./misc ./build/projects/pmut

echo "@-! CLEARING RELEASE"
rm -v -r ./release/*

echo "@-! MOVING APP FILES TO RELEASE"
mv -v ./build/projects/pmut/pmut ./release
mv -v ./build/projects/pmut/misc ./release

echo "@-! RUNNING APP"
./release/pmut

echo "@-! APP FINISHED"