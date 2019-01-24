find replaceOutput/ -name "*.class" -type f -print -exec rm -rf {} \;
find replaceOutput/ -name "*.jar" -type f -print -exec rm -rf {} \;
echo "ok1"
java -Xms512M -Xmx1024M -cp ../soot-lib/symja-2015-09-26.jar:../soot-lib/jasminclasses-custom.jar:../soot-lib/polyglotclasses-1.3.5.jar:../soot-lib/soot-trunk.jar:../soot-lib/commons-io-2.4.jar:../soot-lib/log4j-1.2.11.jar:../CFHiderNew/testcase.jar MyMain -cp .:$JAVA_HOME/jre/lib/rt.jar:$JAVA_HOME/jre/lib/jce.jar:../soot-lib/hadoop-core-0.20.205.1.jar:../soot-lib/hadoop-tools-0.20.205.1.jar:../soot-lib/commons-logging-1.1.3.jar:../lib/commons-cli-1.2.jar  -src-prec java -f c -include-all -process-dir src -output-dir replaceOutput
echo "ok2"
