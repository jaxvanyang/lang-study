public class AndroidFactory implements SystemFactory {
	@Override
	public OperationController createOperationController() {
		return new AndroidOperationController();
	}

	@Override
	public UiController createUiController() {
		return new AndroidUiController();
	}
}
