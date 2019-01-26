package FakeSegmentForJni;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class WordCount {

  public static class TokenizerMapper 
       extends Mapper<Object, Text, Text, IntWritable>{
    
    private final static IntWritable one = new IntWritable(1);
    private Text word = new Text();
      
    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
      StringTokenizer itr = new StringTokenizer(value.toString());
      

     //System.out.println(sgx_invoker.print_ms());
     //sgx_invoker.init();
      while (itr.hasMoreTokens()) {
	//String temp=itr.nextToken();
	//System.out.println(temp);
        //word.set(temp);
	word.set(itr.nextToken());
        context.write(word, one);
      }
    }
  }
  
  public static class IntSumReducer 
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();

    public void reduce(Text key, Iterable<IntWritable> values, 
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
      for (IntWritable val : values) {
        sum += val.get();
      }
      result.set(sum);
      context.write(key, result);
    }
  }

  public static void main(String[] args) throws Exception {
	
	System.out.println ("In this project, we test wordcount with SGX!\n");

	Configuration conf = new Configuration();
	GenericOptionsParser goparser = new GenericOptionsParser(conf, args);
	String otherargs [] = goparser.getRemainingArgs();

   // String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
   // if (otherArgs.length != 2) {
     // System.err.println("Usage: wordcount <in> <out>");
      //System.exit(2);
    //}
    Job job = new Job(conf, "word count");
    job.setJarByClass(WordCount.class);

    job.setMapperClass(TokenizerMapper.class);
    job.setCombinerClass(IntSumReducer.class);
    job.setReducerClass(IntSumReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    FileInputFormat.addInputPath(job, new Path(otherargs[0]));
    FileOutputFormat.setOutputPath(job, new Path(otherargs[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
