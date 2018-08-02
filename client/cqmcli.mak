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
PROJECT = cqmcli.exe
OBJFILES = cqmcli.obj ..\common\client\stuff.obj ..\common\client\globcli.obj \
    ..\common\client\fmain.obj ..\common\client\fcustomashgraph.obj \
    ..\common\windows\fdm.obj ..\common\windows\global.obj \
    ..\common\windows\fmsgs.obj ..\common\windows\logfile.obj \
    ..\common\windows\fclock.obj ..\common\classes\cqmdiag.obj \
    ..\common\client\fcustomminutes.obj ..\common\windows\fpromku.obj \
    ..\common\client\fselectpointdate.obj ..\common\client\clientdata.obj \
    ..\common\client\rhours.obj ..\common\classes\coalheap.obj \
    ..\common\classes\defines.obj ..\common\client\rashgraph.obj \
    ..\common\client\fcustomvagonsviewer.obj \
    ..\common\client\fcustomvagonseditor.obj ..\common\client\rvagons.obj \
    ..\common\client\rpos.obj ..\common\client\rmin.obj \
    ..\common\client\findic.obj ..\common\client\fpositseditor.obj \
    ..\common\client\rcert.obj ..\common\client\foperhelp.obj \
    ..\common\windows\floader.obj ..\common\windows\fenterdata.obj \
    ..\common\client\cqmnet.obj ..\common\client\froutes.obj \
    ..\common\client\faccums.obj ..\common\client\fvagonbatch.obj \
    ..\common\client\frepreview.obj ..\common\client\falarm.obj \
    ..\common\client\clialarmthread.obj ..\common\client\rintervals.obj \
    ..\common\classes\cqmstreamparse.obj ..\common\classes\cqmversion.obj \
    ..\common\client\rmonth.obj
RESFILES = cqmcli.res
MAINSOURCE = cqmcli.cpp
RESDEPEN = $(RESFILES) ..\common\client\fmain.dfm \
    ..\common\client\fcustomashgraph.dfm ..\common\windows\fdm.dfm \
    ..\common\windows\fmsgs.dfm ..\common\windows\fclock.dfm \
    ..\common\client\fcustomminutes.dfm ..\common\windows\fpromku.dfm \
    ..\common\client\fselectpointdate.dfm ..\common\client\rhours.dfm \
    ..\common\client\rashgraph.dfm ..\common\client\fcustomvagonsviewer.dfm \
    ..\common\client\fcustomvagonseditor.dfm ..\common\client\rvagons.dfm \
    ..\common\client\rpos.dfm ..\common\client\rmin.dfm \
    ..\common\client\findic.dfm ..\common\client\fpositseditor.dfm \
    ..\common\client\rcert.dfm ..\common\client\foperhelp.dfm \
    ..\common\windows\floader.dfm ..\common\windows\fenterdata.dfm \
    ..\common\client\froutes.dfm ..\common\client\faccums.dfm \
    ..\common\client\fvagonbatch.dfm ..\common\client\frepreview.dfm \
    ..\common\client\falarm.dfm ..\common\client\rintervals.dfm
LIBFILES = 
IDLFILES = 
IDLGENFILES = 
LIBRARIES = ZParseSql.lib ZDbc.lib ZCore.lib ZPlain.lib ZComponent.lib teeui.lib \
    teeqr.lib bdertl.lib vclx.lib qrpt.lib vcldb.lib dbrtl.lib tee.lib \
    teedb.lib vcl.lib rtl.lib
PACKAGES = dbrtl.bpi vcldb.bpi teedb.bpi tee.bpi teeqr.bpi
SPARELIBS = rtl.lib vcl.lib teedb.lib tee.lib dbrtl.lib vcldb.lib qrpt.lib vclx.lib \
    bdertl.lib teeqr.lib teeui.lib ZComponent.lib ZPlain.lib ZCore.lib \
    ZDbc.lib ZParseSql.lib
DEFFILE = 
OTHERFILES = 
# ---------------------------------------------------------------------------
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = _DEBUG;CQM_ON_WINDOWS;CQM_CLIENT_APPLICATION;FIREBIRD15
SYSDEFINES = NO_STRICT
INCLUDEPATH = ..;..\common\client;..\common\classes;..\common\windows;$(BCB)\include;$(BCB)\include\vcl;$(BCB)\zeosdbo\src\core;$(BCB)\zeosdbo\src\component;$(BCB)\zeosdbo\src\dbc;$(BCB)\zeosdbo\src\parsesql;$(BCB)\zeosdbo\src\plain
LIBPATH = ..;..\common\client;..\common\classes;..\common\windows;$(BCB)\Projects\Lib;$(BCB)\lib\obj;$(BCB)\lib;$(BCB)\zeosdbo\packages\cbuilder6\build
WARNINGS= -w-par -w-asc
PATHCPP = .;..\common\client;..\common\windows;..\common\classes
PATHASM = .;
PATHPAS = .;
PATHRC = .;
PATHOBJ = .;$(LIBPATH)
# ---------------------------------------------------------------------------
CFLAG1 = -O2 -H=$(BCB)\lib\vcl6.csm -Hc -Q -Vx -Ve -xp -fp -X- -r- -a8 -5 -b- -d -k \
    -y -v -vi- -c -tW -tWM
IDLCFLAGS = -I.. -I..\common\client -I..\common\classes \
    -I"C:\Program Files\Borland\CBuilder5\Projects\." -I..\common\windows \
    -I$(BCB)\include -I$(BCB)\include\vcl -I$(BCB)\zeos\zeosdbo \
    -I$(BCB)\zeos\zeosdbo\common -I$(BCB)\zeos\zeosdbo\dbase -src_suffix cpp \
    -D_DEBUG -boa
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




