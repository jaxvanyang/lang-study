public class Main {
	public static void main(String[] args) {
		ReaderFactory jpgReaderFactory = new JpgReaderFactory();
		Reader jpgReader = jpgReaderFactory.getReader();
		jpgReader.read();


		ReaderFactory pngReaderFactory = new PngReaderFactory();
		Reader pngReader = pngReaderFactory.getReader();
		pngReader.read();

		ReaderFactory gifReaderFactory = new GifReaderFactory();
		Reader gifReader = gifReaderFactory.getReader();
		gifReader.read();
	}
}
