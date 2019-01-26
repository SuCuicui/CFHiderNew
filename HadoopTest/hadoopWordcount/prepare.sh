/home/xidian/hadoop/bin/hadoop dfs -rmr wc_input

/home/xidian/hadoop/bin/hadoop fs -mkdir wc_input
/home/xidian/hadoop/bin/hadoop fs -put /home/xidian/hadoop-tsetcase/hadoopWordcount/text/* wc_input

#/home/xidian/hadoop/bin/hadoop dfs -ls wc_input
#/home/xidian/hadoop/bin/hadoop fs -cat wc_input/*
