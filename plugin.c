#include <npapi.h>
#include <npfunctions.h>
#include <CoreFoundation/CoreFoundation.h>

static NPNetscapeFuncs* npnfuncs;

#pragma mark Plugin Class

static const char *plugin_method_name_open = "open";

bool plugin_has_method(NPObject *obj, NPIdentifier methodName) {
	NPUTF8 *name = npnfuncs->utf8fromidentifier(methodName);
	bool result = strcmp(name, plugin_method_name_open) == 0;
	npnfuncs->memfree(name);
	return result;
}

bool plugin_invoke(NPObject *obj, NPIdentifier methodName, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	NPUTF8 *name = npnfuncs->utf8fromidentifier(methodName);
	if(strcmp(name, plugin_method_name_open) == 0) {
		npnfuncs->memfree(name);
		if(argCount < 1) {
			npnfuncs->setexception(obj, "At least one argument is required.");
			return false;
		}
		if(! NPVARIANT_IS_STRING(args[0])) {
			npnfuncs->setexception(obj, "The first argument must be String.");
			return false;
		}

		CFURLRef url = CFURLCreateWithBytes(NULL, (const UInt8 *)NPVARIANT_TO_STRING(args[0]).UTF8Characters, NPVARIANT_TO_STRING(args[0]).UTF8Length, kCFStringEncodingUTF8, NULL);
		if(url) {
			LSOpenCFURLRef(url, NULL);
		}
		CFRelease(url);

		return true;
	}
	npnfuncs->memfree(name);
	return false;
}

static struct NPClass plugin_class = {
	NP_CLASS_STRUCT_VERSION,
	NULL,
	NULL,
	NULL,
	plugin_has_method,
	plugin_invoke,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};
static NPObject *plugin_instance;

#pragma mark -
#pragma mark Plugin Functions

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved) {
	return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData** save) {
	if(!plugin_instance) {
		npnfuncs->releaseobject(plugin_instance);
		plugin_instance = NULL;
	}
	return NPERR_NO_ERROR;
}

NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value) {
	switch(variable) {
		case NPPVpluginScriptableNPObject:
			if(!plugin_instance) {
				plugin_instance = npnfuncs->createobject(instance, &plugin_class);
				npnfuncs->retainobject(plugin_instance);
			}
			*(NPObject **)value = plugin_instance;
			break;
		default:
			return NPERR_GENERIC_ERROR;
	}
	return NPERR_NO_ERROR;
}

#pragma mark -
#pragma mark Initialization

NPError NP_Initialize(NPNetscapeFuncs* browserFuncs) {  
	npnfuncs = browserFuncs;
	return NPERR_NO_ERROR;
}

NPError NP_GetEntryPoints(NPPluginFuncs* pluginFuncs) {
	pluginFuncs->version = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
	pluginFuncs->size = sizeof(pluginFuncs);
	pluginFuncs->newp = NPP_New;
	pluginFuncs->destroy = NPP_Destroy;
	pluginFuncs->getvalue = NPP_GetValue;
	return NPERR_NO_ERROR;
}

void NP_Shutdown(void) {
}