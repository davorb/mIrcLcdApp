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

		text=text.replace('�', 'a');
		text=text.replace('�', 'a');
		text=text.replace('�', 'o');
		text=text.replace('�', 'A');
		text=text.replace('�', 'A');
		text=text.replace('�', 'O');
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
