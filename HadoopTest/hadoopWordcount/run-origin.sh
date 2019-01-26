
/home/xidian/hadoop/bin/hadoop dfs -rmr /user/xidian/wc_output

time /home/xidian/hadoop/bin/hadoop jar /home/xidian/hadoop/hadoop-examples-1.0.4.jar wordcount wc_input wc_output
