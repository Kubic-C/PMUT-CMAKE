mkdir build
mkdir release
cd build

clear
echo "@-! CMAKE GENERATING PROJECT"
cmake .. -G Ninja

echo ""
echo ""
echo "@-! NINJA BUILDING APP"
ninja

echo ""
echo ""
echo "@-! CLEARING RELEASE"
cd ..
rm -v -r ./release/*

echo ""
echo ""
echo "@-! COPYING DEPENDENCIES"
cp  -v -r ./misc ./release
cp  -v -r ./LICENSE ./release

echo ""
echo ""
echo "@-! MOVING APP FILES TO RELEASE"
mv -v ./build/projects/pmut/pmut ./release

echo ""
echo ""
echo "@-! RUNNING APP"
./release/pmut

echo "@-! APP FINISHED"