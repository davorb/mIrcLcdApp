import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;


public class ParseLogdirectory {

	String filter, extension;
	ArrayList<String> fileNames;
	File dir;
	File[] files;

	public ParseLogdirectory(String dirName, String filter, String extension) {
		dir = new File(dirName);			
		fileNames = new ArrayList<String>();
		this.filter = filter;
		this.extension = extension;
	}

	public String parse() throws IOException {
		files = dir.listFiles(new NameContainsFilter(filter));	

		if (files.length < 1)
			throw new IOException("Directory was empty");
		for (int i=0; i < files.length; i++) {
			String fileName = files[i].getName();
			fileName = fileName.substring(filter.length());

			// This is a fix to remove the #channelname.network.[0-9].log files
			if (fileName.length() > 7) {
				fileName = fileName.substring(0, fileName.length()-extension.length());
				fileNames.add(new String(fileName.toLowerCase()));
			}
		}
		Collections.sort(fileNames);
		if (fileNames.size() == 0)
			throw new IOException("No log files that matched the pattern were found.");
		return dir.getAbsolutePath()+"\\"+filter+fileNames.get(fileNames.size()-1)+extension;	
	}
}
