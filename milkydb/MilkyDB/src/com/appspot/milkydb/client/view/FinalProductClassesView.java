package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.FinalProductClassesPresenter.Display;

public class FinalProductClassesView extends AbstractProductClassesView implements
		Display {

	@Override
	protected String getTableTitle() {
		return "Классы готовой продукции";
	}

}
