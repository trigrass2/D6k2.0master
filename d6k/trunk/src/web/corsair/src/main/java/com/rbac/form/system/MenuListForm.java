/*
 * Generated by MyEclipse Struts
 * Template path: templates/java/JavaClass.vtl
 */
package com.rbac.form.system;

/**
 * MyEclipse Struts
 * Creation date: 05-04-2014
 * 
 * XDoclet definition:
 * @struts.form name="menuListForm"
 */
public class MenuListForm{
	
	private String query;
	
	private String del;
	
	private String deleteIds;
	
	private String nameQry;
	
	private String urlQry;

//	/**
//	 * Method validate
//	 * @param mapping
//	 * @param request
//	 * @return ActionErrors
//	 */
//	public ActionErrors validate(ActionMapping mapping,
//			HttpServletRequest request) {
//		// TODO Auto-generated method stub
//		return null;
//	}
//
//	/**
//	 * Method reset
//	 * @param mapping
//	 * @param request
//	 */
//	public void reset(ActionMapping mapping, HttpServletRequest request) {
//		this.query = null;
//		this.del = null;
//	}

	public String getDel() {
		return del;
	}

	public void setDel(String del) {
		this.del = del;
	}

	public String getDeleteIds() {
		return deleteIds;
	}

	public void setDeleteIds(String deleteIds) {
		this.deleteIds = deleteIds;
	}

	public String getNameQry() {
		return nameQry;
	}

	public void setNameQry(String nameQry) {
		this.nameQry = nameQry;
	}

	public String getQuery() {
		return query;
	}

	public void setQuery(String query) {
		this.query = query;
	}

	public String getUrlQry() {
		return urlQry;
	}

	public void setUrlQry(String urlQry) {
		this.urlQry = urlQry;
	}
}