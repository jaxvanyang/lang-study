public class IosFactory implements SystemFactory {
	@Override
	public OperationController createOperationController() {
		return new IosOperationController();
	}

	@Override
	public UiController createUiController() {
		return new IosUiController();
	}
}
