/**
 * 
 */
package com.appspot.milkydb.shared;

/**
 * @author burdakovd
 * 
 */
public interface HasRelations {
	/**
	 * Проверяет, есть ли классы, ссылающиеся на этот. Используется в функции
	 * удаления для проверки, можно ли удалять этот объект.
	 * 
	 * @return true если в хранилище есть ссылки на этот объект, которые не дают
	 *         его удалить.
	 */
	boolean hasRelations();
}
