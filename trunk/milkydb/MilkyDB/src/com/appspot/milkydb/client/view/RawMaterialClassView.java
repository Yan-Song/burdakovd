package com.appspot.milkydb.client.view;

import com.appspot.milkydb.client.presenter.RawMaterialClassPresenter;

public class RawMaterialClassView extends AbstractProductClassView implements
		RawMaterialClassPresenter.Display {

	@Override
	protected String getTableTitle() {
		return "Классы сырья";
	}

}
