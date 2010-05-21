package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.FinalProductClassPresenter.Display;

public class FinalProductClassView extends AbstractProductClassView implements
		Display {

	@Override
	protected String getTableTitle() {
		return "Классы готовой продукции";
	}

}
