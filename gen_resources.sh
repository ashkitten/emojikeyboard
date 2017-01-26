echo "<!DOCTYPE RCC><RCC version=\"1.0\">" > resources.qrc
echo "<qresource>" >> resources.qrc
find ./res/ -type f | sed "s/^\.\/res\/\(.*\)/    <file alias=\"\1\">res\/\1<\/file>/g" >> resources.qrc
echo "</qresource>" >> resources.qrc
echo "</RCC>" >> resources.qrc
