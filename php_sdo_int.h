/*
+----------------------------------------------------------------------+
| Copyright IBM Corporation 2005, 2007.                                |
| All Rights Reserved.                                                 |
+----------------------------------------------------------------------+
|                                                                      |
| Licensed under the Apache License, Version 2.0 (the "License"); you  |
| may not use this file except in compliance with the License. You may |
| obtain a copy of the License at                                      |
| http://www.apache.org/licenses/LICENSE-2.0                           |
|                                                                      |
| Unless required by applicable law or agreed to in writing, software  |
| distributed under the License is distributed on an "AS IS" BASIS,    |
| WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
| implied. See the License for the specific language governing         |
| permissions and limitations under the License.                       |
+----------------------------------------------------------------------+
| Author: Caroline Maynard                                             |
+----------------------------------------------------------------------+

*/
/* $Id: php_sdo_int.h,v 1.28 2008/03/03 17:56:37 mfp Exp $ */
#ifndef PHP_SDO_INT_H
#define PHP_SDO_INT_H

/*
 * Declarations intended for use internal to the SDO extension
 */
#include "php_sdo.h"

#include <sstream>

#include "commonj/sdo/SDOSPI.h"

using namespace commonj::sdo;
using std::ostringstream;

#define SDO_VERSION "1.2.4"

#define SDO_NAMESPACE_URI "namespaceURI"
#define SDO_TYPE_NAME     "typeName"

#define SDO_USER_DATA_EMPTY 0xffffffff

#define SDO_TOSTRING_MAX 1024

enum sdo_changesummary_type {
	CS_NONE = 0,
	CS_MODIFICATION = 1,
	CS_ADDITION = 2,
	CS_DELETION = 3
};

enum sdo_write_type {
	TYPE_APPEND = 1001,
	TYPE_INSERT,
	TYPE_OVERWRITE
};

extern PHP_SDO_API zend_class_entry *sdo_dataobject_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_dataobjectimpl_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_list_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_dataobjectlist_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_changeddataobjectlist_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_sequence_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_sequenceimpl_class_entry;

extern PHP_SDO_API zend_class_entry *sdo_das_datafactory_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_das_datafactoryimpl_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_das_dataobject_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_das_setting_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_das_settinglist_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_das_changesummary_class_entry;

extern PHP_SDO_API zend_class_entry *sdo_model_type_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_model_typeimpl_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_model_property_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_model_propertyimpl_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_model_reflectiondataobject_class_entry;

extern PHP_SDO_API zend_class_entry *sdo_exception_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_typenotfoundexception_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_propertynotsetexception_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_propertynotfoundexception_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_invalidconversionexception_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_indexoutofboundsexception_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_unsupportedoperationexception_class_entry;
extern PHP_SDO_API zend_class_entry *sdo_cppexception_class_entry;

extern PHP_SDO_API void sdo_das_df_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_das_df_new(zval *me, DataFactoryPtr dfp TSRMLS_DC);
extern PHP_SDO_API DataFactoryPtr sdo_das_df_get(zval *me TSRMLS_DC);

extern PHP_SDO_API void sdo_do_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_do_new(zval *me, DataObjectPtr dop TSRMLS_DC);
extern PHP_SDO_API DataObjectPtr sdo_do_get(zval *me TSRMLS_DC);

extern PHP_SDO_API void sdo_list_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_dataobjectlist_new(zval *me, const Type& typeh, DataObjectPtr dop, DataObjectList *listh TSRMLS_DC);
extern PHP_SDO_API void sdo_changeddataobjectlist_new(zval *me, const ChangedDataObjectList *listh TSRMLS_DC);
extern PHP_SDO_API void sdo_das_settinglist_new(zval *me, SettingList& listh TSRMLS_DC);
extern PHP_SDO_API int  sdo_list_count_elements(zval *object, long *count TSRMLS_DC);

extern PHP_SDO_API void sdo_das_changesummary_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_das_changesummary_new(zval *me, ChangeSummary *change_summary TSRMLS_DC);

extern PHP_SDO_API void sdo_das_setting_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_das_setting_new(zval *me, Setting *setting TSRMLS_DC);

extern PHP_SDO_API void sdo_sequence_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_sequence_new(zval *me, SequencePtr seqp TSRMLS_DC);

extern PHP_SDO_API void sdo_model_type_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_model_type_new(zval *me, const Type *typep TSRMLS_DC);
extern PHP_SDO_API void sdo_model_type_summary_string (ostringstream& print_buf, const Type *typep TSRMLS_DC);
extern PHP_SDO_API void sdo_model_type_string (ostringstream& print_buf, const Type *typep, const char *indent TSRMLS_DC);
extern PHP_SDO_API void sdo_model_property_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_model_property_new(zval *me, const Property *propertyp TSRMLS_DC);
extern PHP_SDO_API const Property *sdo_model_property_get_property(zval *me TSRMLS_DC);
extern PHP_SDO_API void sdo_model_property_string (ostringstream& print_buf, const Property *propertyp, const char *indent TSRMLS_DC);

extern PHP_SDO_API void sdo_model_rdo_minit(zend_class_entry *tmp TSRMLS_DC);

extern PHP_SDO_API zval *sdo_throw_exception(zend_class_entry *ce, const char *message, long code, zval *z_cause TSRMLS_DC);
extern PHP_SDO_API zval *sdo_throw_exception_ex(zend_class_entry *ce, long code, zval *z_cause TSRMLS_DC, char *format, ...);
extern PHP_SDO_API void sdo_exception_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_exception_new(zval *me, zend_class_entry *ce, const char *message, long code, zval *cause TSRMLS_DC);
extern PHP_SDO_API zend_function_entry *sdo_exception_get_methods();
extern PHP_SDO_API zval *sdo_throw_runtimeexception(SDORuntimeException *e TSRMLS_DC);
extern PHP_SDO_API void sdo_cppexception_minit(zend_class_entry *tmp TSRMLS_DC);
extern PHP_SDO_API void sdo_cppexception_new(zval *me, SDORuntimeException *cpp_exception TSRMLS_DC);

extern PHP_SDO_API void sdo_make_long_class_constant(zend_class_entry *ce, char *name, long value);
void sdo_init_properties_hash(zend_object *zo_ptr);
void sdo_destroy_properties_hash(zend_object *zo_ptr);

extern PHP_SDO_API int sdo_parse_offset_param(DataObjectPtr dop, zval *z_offset,
	const Property **return_property, const char **return_xpath, int property_required, int quiet TSRMLS_DC);
extern PHP_SDO_API Type::Types sdo_map_zval_type (zval *z_value);

/* {{{ refcount handling macros for forward compatibility
 */
#ifndef Z_ADDREF_P
#define Z_ADDREF_P(x) (x)->refcount++
#endif

#ifndef Z_SET_REFCOUNT_P
#define Z_SET_REFCOUNT_P(x, n) (x)->refcount = n
#endif

#ifndef Z_UNSET_ISREF_P
#define Z_UNSET_ISREF_P(x) (x)->is_ref = 0
#endif
/* }}} */

/* {{{ object memory debugging macros
 */
#ifdef SDO_DEBUG_OBJECTS

#define SDO_DEBUG_ALLOCATE(handle,object) \
    fprintf(stderr, "Allocating " CLASS_NAME " id #%d at 0x%x\n", (handle), (object))

#define SDO_FUNC_ADDREF(prefix) sdo_##prefix##_add_ref
#define SDO_FUNC_DELREF(prefix) sdo_##prefix##_del_ref
#define SDO_FUNC_DESTROY(prefix) sdo_##prefix##_destroy_object

#define SDO_DEBUG_ADDREF(prefix) \
static void sdo_##prefix##_add_ref(zval *object TSRMLS_DC) { \
	fprintf(stderr, "Incrementing refcount for " CLASS_NAME " id #%d\n", object->value.obj.handle); \
    zend_objects_store_add_ref(object TSRMLS_CC); \
}

#define SDO_DEBUG_DELREF(prefix) \
static void sdo_##prefix##_del_ref(zval *object TSRMLS_DC) { \
	fprintf(stderr, "Decrementing refcount for " CLASS_NAME " id #%d\n", object->value.obj.handle); \
    zend_objects_store_del_ref(object TSRMLS_CC); \
}

#define SDO_DEBUG_DESTROY(prefix) \
static void sdo_##prefix##_destroy_object(void *object, zend_object_handle handle TSRMLS_DC) { \
    fprintf(stderr, "Destroying " CLASS_NAME " id #%d at 0x%x\n", handle, object); \
    zend_objects_destroy_object((zend_object *)object, handle TSRMLS_CC); \
}

#define SDO_DEBUG_FREE(object) \
    fprintf(stderr, "Freeing " CLASS_NAME " at 0x%x\n", (object))

#else

#define SDO_DEBUG_ALLOCATE(handle,object)
#define SDO_FUNC_ADDREF(prefix) zend_objects_store_add_ref
#define SDO_FUNC_DELREF(prefix) zend_objects_store_del_ref
#define SDO_FUNC_DESTROY(prefix) NULL
#define SDO_DEBUG_ADDREF(prefix)
#define SDO_DEBUG_DELREF(prefix)
#define SDO_DEBUG_DESTROY(prefix)
#define SDO_DEBUG_FREE(object)

#endif
/* }}} */

#endif	/* PHP_SDO_INT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
