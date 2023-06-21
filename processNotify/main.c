#include "ntddk.h"
#include "wdm.h"

VOID PcreateProcessNotifyRoutineEx(PEPROCESS Process,HANDLE ProcessId,PPS_CREATE_NOTIFY_INFO CreateInfo){
	if (CreateInfo) {
		DbgPrint("[Process Create] %i \r\n", ProcessId);
		//CreateInfo->CreationStatus = STATUS_ACCESS_DENIED;
		CreateInfo->CreationStatus = STATUS_SUCCESS;
	}
}

VOID Unload(PDRIVER_OBJECT driverObject) {

	DbgPrint("UNLOAD DRIVER");
	PsSetCreateProcessNotifyRoutineEx(PcreateProcessNotifyRoutineEx, TRUE);
	
}
NTSTATUS DriverEntry(PDRIVER_OBJECT driverObject, PUNICODE_STRING registryPath) {
	
	NTSTATUS status;
	DbgPrint("LOAD DRIVER");
	driverObject->DriverUnload = Unload;
	
	status = PsSetCreateProcessNotifyRoutineEx(PcreateProcessNotifyRoutineEx,FALSE);
	if (!NT_SUCCESS(status)) {
		DbgPrint("LOAD DRIVER BOOOOOSSSS");
		return status;
	}
	return STATUS_SUCCESS;


}