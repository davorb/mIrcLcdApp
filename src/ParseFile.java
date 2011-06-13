import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;


public class ParseFile {
	BufferedReader reader;

	public ParseFile(String fileName) throws FileNotFoundException {
		FileInputStream fstream = new FileInputStream(fileName);	
		DataInputStream in = new DataInputStream(fstream);
		this.reader = new BufferedReader(new InputStreamReader(in));
	}

	public String parse() {
		return filterLetters(getLastLine()); // TODO: parsing
	}

	private String filterLetters(String text) {

		text=text.replace('å', 'a');
		text=text.replace('ä', 'a');
		text=text.replace('ö', 'o');
		text=text.replace('Å', 'A');
		text=text.replace('Ä', 'A');
		text=text.replace('Ö', 'O');
		return text;
	}

	private String getLastLine() {
		String line="";
		try {
			while (reader.ready()) {
				line = reader.readLine();
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return line;
	}
}
