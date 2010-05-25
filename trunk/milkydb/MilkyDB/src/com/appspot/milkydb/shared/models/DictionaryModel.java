/**
 * 
 */
package com.appspot.milkydb.shared.models;

/**
 * @author burdakovd
 * 
 */
@SuppressWarnings("serial")
public class DictionaryModel extends SingleStringModel {

	private Integer linkCount = 0;

	/**
	 * 
	 */
	public DictionaryModel() {
	}

	public Integer getLinkCount() {
		return linkCount;
	}

	public void setLinkCount(final Integer linkCount) {
		this.linkCount = linkCount;
	}

}
