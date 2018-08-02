# ---------------------------------------------------------------------------
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

# ---------------------------------------------------------------------------
# IDE SECTION
# ---------------------------------------------------------------------------
# The following section of the project makefile is managed by the BCB IDE.
# It is recommended to use the IDE to change any of the values in this
# section.
# ---------------------------------------------------------------------------

VERSION = BCB.06.00
# ---------------------------------------------------------------------------
PROJECT = cqmsrv.exe
OBJFILES = cqmsrv.obj ..\common\classes\coalheap.obj ..\common\classes\cqmcore.obj \
    ..\common\classes\cqmio.obj ..\common\classes\defines.obj \
    ..\common\classes\device.obj ..\common\classes\signals.obj \
    ..\common\classes\pcl836.obj ..\common\server\fmain.obj \
    ..\common\windows\fdm.obj ..\common\windows\fsignals.obj \
    ..\common\windows\tiothread.obj ..\common\windows\global.obj \
    ..\common\windows\fmsgs.obj ..\common\windows\stuff.obj \
    ..\common\windows\logfile.obj ..\common\classes\cqmcompute.obj \
    ..\common\windows\dbacts.obj ..\common\windows\ftableviewer.obj \
    ..\common\windows\fenterdata.obj ..\common\windows\fdatetimeselect.obj \
    ..\common\classes\cqmalgorithm.obj ..\common\classes\cqmpoint.obj \
    ..\common\windows\faboutsrv.obj ..\common\classes\cqmvagon.obj \
    ..\common\windows\globsrv.obj ..\common\classes\cqmdiag.obj \
    ..\common\windows\fpromku.obj ..\common\classes\alarms.obj \
    ..\common\windows\Winport32.obj ..\common\classes\dev_a10.obj \
    ..\common\ide\ide.obj ..\common\windows\fpswd.obj \
    ..\common\classes\cqmexec.obj ..\common\classes\cqmvagon_cn.obj \
    ..\common\classes\cqmpoint003.obj ..\common\windows\floader.obj \
    ..\common\windows\shellexec.obj ..\common\classes\cqmfuncs.obj \
    ..\common\huru\hurup.obj ..\common\classes\cqmstreamparse.obj \
    ..\common\classes\cqmtraffic.obj ..\common\classes\cqmroute.obj \
    ..\common\classes\cqmaccumulator.obj ..\common\windows\cqmsecurity.obj \
    ..\common\classes\cqmentity.obj ..\common\classes\cqmpointg.obj \
    ..\common\classes\cqmvagontipper.obj ..\common\classes\cqmcustomvagon.obj \
    ..\common\windows\alarmthread.obj ..\common\windows\fcteditor.obj \
    ..\common\classes\cqmcoalqueue.obj ..\common\classes\cqmvagon_q.obj \
    ..\common\windows\fclock.obj ..\common\classes\cqmversion.obj \
    ..\common\classes\cqmextensions.obj ..\common\classes\coalqueue.obj
RESFILES = cqmsrv.res
MAINSOURCE = cqmsrv.cpp
RESDEPEN = $(RESFILES) ..\common\server\fmain.dfm ..\common\windows\fdm.dfm \
    ..\common\windows\fsignals.dfm ..\common\windows\fmsgs.dfm \
    ..\common\windows\ftableviewer.dfm ..\common\windows\fenterdata.dfm \
    ..\common\windows\fdatetimeselect.dfm ..\common\windows\faboutsrv.dfm \
    ..\common\windows\fpromku.dfm ..\common\windows\fpswd.dfm \
    ..\common\windows\floader.dfm ..\common\windows\fcteditor.dfm \
    ..\common\windows\fclock.dfm
LIBFILES = 
IDLFILES = 
IDLGENFILES = 
LIBRARIES = ZParseSql.lib ZDbc.lib ZCore.lib ZPlain.lib ZComponent.lib vclx.lib \
    bcbsmp.lib vcldb.lib dbrtl.lib vcl.lib rtl.lib
PACKAGES = dbrtl.bpi vcldb.bpi
SPARELIBS = rtl.lib vcl.lib dbrtl.lib vcldb.lib bcbsmp.lib vclx.lib ZComponent.lib \
    ZPlain.lib ZCore.lib ZDbc.lib ZParseSql.lib
DEFFILE = 
OTHERFILES = 
# ---------------------------------------------------------------------------
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = _DEBUG;CQM_ON_WINDOWS;FIREBIRD15;CQM_SERVER_APPLICATION
SYSDEFINES = NO_STRICT
INCLUDEPATH = ..;..\extensions;..\common\server;..\common\huru;..\common\ide;..\common\windows;..\common\classes;$(BCB)\zeosdbo\src\core;$(BCB)\zeosdbo\src\dbc;$(BCB)\zeosdbo\src\parsesql;$(BCB)\zeosdbo\src\plain;$(BCB)\zeosdbo\src\component;$(BCB)\include;$(BCB)\include\vcl;"C:\Program Files\Borland\CBuilder5\Projects"
LIBPATH = ..;..\extensions;..\common\server;..\common\huru;..\common\ide;..\common\windows;..\common\classes;$(BCB)\zeosdbo\packages\cbuilder6\build;$(BCB)\Projects\Lib;$(BCB)\lib\obj;$(BCB)\lib
WARNINGS= -w8092 -w8091 -w8090 -w8089 -w8087 -wprc -wuse -wucp -wstv -wstu -wpin \
    -w-par -wnod -wnak -wdef -wcln -wbbf -wasm -wamp -wamb
PATHCPP = .;..\common\classes;..\common\server;..\common\windows;..\common\ide;..\common\huru
PATHASM = .;
PATHPAS = .;
PATHRC = .;
PATHOBJ = .;$(LIBPATH)
# ---------------------------------------------------------------------------
CFLAG1 = -Od -H=$(BCB)\lib\vcl6.csm -Hc -Q -Vx -Ve -X- -r- -a8 -6 -b -d -k -y -v \
    -vi- -c -tW -tWM -w-asc
IDLCFLAGS = -I.. -I..\common\server -I..\common\huru -I..\common\ide \
    -I"C:\Program Files\Borland\CBuilder5\Projects\." -I..\common\windows \
    -I..\common\classes -I$(BCB)\include -I$(BCB)\include\vcl \
    -I$(BCB)\zeos\zeosdbo -I$(BCB)\zeos\zeosdbo\common \
    -I$(BCB)\zeos\zeosdbo\dbase -src_suffix cpp -D_DEBUG -boa
PFLAGS = -$Y+ -$W -$O- -$A8 -v -JPHNE -M
RFLAGS = 
AFLAGS = /mx /w2 /zi
LFLAGS = -D"" -aa -Tpe -x -Gn -v
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj sysinit.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib
# ---------------------------------------------------------------------------
!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

!endif





# ---------------------------------------------------------------------------
# MAKE SECTION
# ---------------------------------------------------------------------------
# This section of the project file is not used by the BCB IDE.  It is for
# the benefit of building from the command-line using the MAKE utility.
# ---------------------------------------------------------------------------

.autodepend
# ---------------------------------------------------------------------------
!if "$(USERDEFINES)" != ""
AUSERDEFINES = -d$(USERDEFINES:;= -d)
!else
AUSERDEFINES =
!endif

!if !$d(BCC32)
BCC32 = bcc32
!endif

!if !$d(CPP32)
CPP32 = cpp32
!endif

!if !$d(DCC32)
DCC32 = dcc32
!endif

!if !$d(TASM32)
TASM32 = tasm32
!endif

!if !$d(LINKER)
LINKER = ilink32
!endif

!if !$d(BRCC32)
BRCC32 = brcc32
!endif


# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

!if $d(PATHPAS)
.PATH.PAS = $(PATHPAS)
!endif

!if $d(PATHASM)
.PATH.ASM = $(PATHASM)
!endif

!if $d(PATHRC)
.PATH.RC  = $(PATHRC)
!endif

!if $d(PATHOBJ)
.PATH.OBJ  = $(PATHOBJ)
!endif
# ---------------------------------------------------------------------------
$(PROJECT): $(OTHERFILES) $(IDLGENFILES) $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) -L$(LIBPATH) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES)
!
# ---------------------------------------------------------------------------
.pas.hpp:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.pas.obj:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.cpp.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.asm.obj:
    $(BCB)\BIN\$(TASM32) $(AFLAGS) -i$(INCLUDEPATH:;= -i) $(AUSERDEFINES) -d$(SYSDEFINES:;= -d) $<, $@

.rc.res:
    $(BCB)\BIN\$(BRCC32) $(RFLAGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -fo$@ $<



# ---------------------------------------------------------------------------




