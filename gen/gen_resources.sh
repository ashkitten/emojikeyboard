cd ${BASH_SOURCE%/*}

cp -r ./emoji-data/emojione/assets/png/ ../res/emoji/png_64
cp -r ./emoji-data/emojione/assets/png_512x512 ../res/emoji/png_512

python3 ./gen_json.py
mv ./emoji.json ../res/emoji.json

echo "<!DOCTYPE RCC><RCC version=\"1.0\">" > ../resources.qrc
echo "<qresource>" >> ../resources.qrc
find ../res/ -type f | sed -e "s/^\.\.\/res\/\(.*\)/    <file alias=\"\1\">res\/\1<\/file>/g" >> ../resources.qrc
echo "</qresource>" >> ../resources.qrc
echo "</RCC>" >> ../resources.qrc
