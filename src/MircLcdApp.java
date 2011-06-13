import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.Runtime;

/*
 * Because of the way the JVM works, one should always
 * add the command line argument -Xmx to limit the
 * size of the heap.
 * 
 * Limiting the size of the stack with -Xss might
 * also be a good idea.
 */
public class MircLcdApp {

	public static void main(String[] args) throws IOException {
		String oldData = "";
		String data;
		ParseFile fileParser;
		ParseLogdirectory dirParser;
		String filename;

		while (true) {
			dirParser = new ParseLogdirectory("C:\\Users\\Davor\\AppData\\Roaming\\mIRC\\logs\\", "#Linero.QuakeNet.", ".log");
			filename = dirParser.parse();
			//System.out.println(filename);
			try {
				fileParser = new ParseFile(filename);
				data = fileParser.parse();
				int a = oldData.compareTo(data);
				if (oldData.compareTo(data) != 0) {
					saveFile("lcddata.txt", data);
					runSerialApp("SerialLogParser.exe");
					oldData = data;
				}
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			dirParser = null;
			filename = null;
			data = null;
			fileParser = null;
			try {
				Thread.currentThread().sleep(5); // 5000
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	private static void saveFile(String fileName, String data) {
		File file = new File(fileName);
		FileWriter fw = null;
		try {
			fw = new FileWriter(file);
			fw.write(data);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			try {
				fw.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} 
	}

	private static void runSerialApp(String appname) {
		try {
			Process pr = Runtime.getRuntime().exec(appname);
			pr.waitFor();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
