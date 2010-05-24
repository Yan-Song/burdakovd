package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.RawMaterialClassesPresenter;

public class RawMaterialClassesView extends AbstractProductClassesView implements
		RawMaterialClassesPresenter.Display {

	@Override
	protected String getTableTitle() {
		return "Классы сырья";
	}

}
