// ---------------------------------------------------------------------------
#ifndef cppMainH
#define cppMainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Ribbon.hpp>
#include <Vcl.RibbonLunaStyleActnCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.RibbonActnMenus.hpp>
#include <Vcl.RibbonObsidianStyleActnCtrls.hpp>


#define KS_APP_URL			_T("http://nikkhokkho.sourceforge.net/static.php?page=FileOptimizer")
#define KS_APP_UPDATE_URL	_T("http://nikkhokkho.sourceforge.net/images/FileOptimizerVersion.txt")

/* Grid columns */
#define KI_GRID_FILE		0
#define KI_GRID_EXTENSION	1
#define KI_GRID_ORIGINAL	2
#define KI_GRID_OPTIMIZED	3
#define KI_GRID_STATUS		4

#define KS_EXTENSION_BMP	_T(" .bmp .dib ")
#define KS_EXTENSION_CSS	_T(" .css ")
#define KS_EXTENSION_DLL	_T(" .dll .bpl .cpl .drv .lzl .ocx .sys .vbx ")
#define KS_EXTENSION_EXE	_T(" .exe .scr ")
#define KS_EXTENSION_FLAC	_T(" .flac ")
#define KS_EXTENSION_GIF	_T(" .gif ")
#define KS_EXTENSION_GZ		_T(" .gz .deb .ipk .tgz .svg .svgz .vlt ")
#define KS_EXTENSION_HTML	_T(" .htm .html .mht .mhtml .xhtml .xml .sgml ")
#define KS_EXTENSION_ICO	_T(" .ico ")
#define KS_EXTENSION_JPG	_T(" .jfi .jif .jfif .jng .jpe .jpg .jpeg .thm ")
#define KS_EXTENSION_JS		_T(" .js .json ")
#define KS_EXTENSION_LUA	_T(" .lua .luac ")
#define KS_EXTENSION_MKV	_T(" .mkv .mka .mks ")
#define KS_EXTENSION_MNG	_T(" .mng ")
#define KS_EXTENSION_MP3	_T(" .mp3 ")
#define KS_EXTENSION_MP4	_T(" .mp4 .3gp .m4a .m4b .m4p .m4r .m4v .acc ")
#define KS_EXTENSION_OBJ	_T(" .obj .o .lib .a ")
#define KS_EXTENSION_OGG	_T(" .ogg ")
#define KS_EXTENSION_OGV	_T(" .ogv ")
#define KS_EXTENSION_OLE	_T(" .chm .chs .chw .doc .dot .fpx .mdb .mdt .mix .mpd .mpp .mpt .msi .msp .mst .one .ost .pps .ppt .pub .puz .rvt .sldasm .sldprt .slddrw stickynotes.snt thumbs.db .vsd .vst .vss .xl .xlc .xlm .xls .xlw .xsf .xsn ")
#define KS_EXTENSION_PCX	_T(" .dcx .pcc .pcx ")
#define KS_EXTENSION_PDF	_T(" .epdf .pdf ")
#define KS_EXTENSION_PNG	_T(" .apng .ico .png ")
#define KS_EXTENSION_SWF	_T(" .swf ")
#define KS_EXTENSION_TAR	_T(" .tar .cbt ")
#define KS_EXTENSION_TIF	_T(" .fax .tif .tiff .ptif .ptiff ")
#define KS_EXTENSION_WEBP	_T(" .webp ")
#define KS_EXTENSION_XML	_T(" .xml .fb2 .fxg .kml .xsl .xslt .xhtml ")
#define KS_EXTENSION_ZIP	_T(" .air .apk .appx .bar .bsz .cbz .cdr .cdt .csl .des .docm .docx .dotx .dotm .dwf .dwfx .easm .epub .fxg .gallery .gallerycollection .galleryitem .grs .ink .ipsw .itz .ipa .ita .jar .kmz .ksf .kmz .mdz .miz .mmip .mvz .mpp .msz .nar .nbk .notebook .odb .odf .odg .odp .ods .odt .oex .osk .oxps .pk3 .ppam .potm .potx .ppsm .ppsx .pptm .pptx .pub .r2skin .rdb .rmskin .s3z .sldm .sldx .stz .swc .vdx .vtx .vsx .wal .wba .wmz .wsz .xap .xlam .xlsm .xlsx .xltm .xltx *.xnk .xmz .xpi .xps .zip ")
#define KS_EXTENSION_MISC	_T(" .aai .avs .fits .jp2 .jpc .hdr .hrz .mif .miff .mtv .otb .p7 .palm .pdb .pbm .pcd .pcds .pfm .pgm .picon .pic .pict .pnm .ppm .psb .psd .sun .vicar .viff .wbmp .xbm .xpm .xwd ")
#define KS_EXTENSION_ALL    (StringReplace((KS_EXTENSION_BMP KS_EXTENSION_CSS KS_EXTENSION_DLL KS_EXTENSION_EXE KS_EXTENSION_FLAC KS_EXTENSION_GIF KS_EXTENSION_GZ KS_EXTENSION_HTML KS_EXTENSION_ICO KS_EXTENSION_JPG KS_EXTENSION_JS KS_EXTENSION_MKV KS_EXTENSION_MNG KS_EXTENSION_MP3 KS_EXTENSION_MP4 KS_EXTENSION_OBJ KS_EXTENSION_OGG KS_EXTENSION_OGV KS_EXTENSION_OLE KS_EXTENSION_PCX KS_EXTENSION_PDF KS_EXTENSION_PNG KS_EXTENSION_SWF KS_EXTENSION_TAR KS_EXTENSION_TIF KS_EXTENSION_WEBP KS_EXTENSION_XML KS_EXTENSION_ZIP KS_EXTENSION_MISC), "  ", " ", TReplaceFlags() << rfReplaceAll))


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct udtOptions
{
	bool bBMPCopyMetadata;
	bool bCSSEnableTidy;
	TCHAR acCSSTemplate[64];
	bool bEXEDisablePETrim;
	bool bGIFCopyMetadata;
	bool bGZCopyMetadata;
	bool bHTMLEnableTidy;
	bool bJPEGCopyMetadata;
	bool bJPEGUseArithmeticEncoding;
	bool bJSEnableJSMin;
	bool bLUAEnableLeanify;
	bool bMiscCopyMetadata;
	bool bMP3CopyMetadata;
	bool bPCXCopyMetadata;
	TCHAR acPDFProfile[64];
	int iPDFCustomDPI;
	bool bPNGCopyMetadata;
	bool bTIFFCopyMetadata;
	bool bXMLEnableLeanify;
	bool bZIPCopyMetadata;
	bool bZIPRecurse;
	bool bDoNotUseRecycleBin;
	bool bKeepAttributes;
	TCHAR acExcludeMask[128];
	bool bBeepWhenDone;
	int iLevel;
	int iProcessPriority;
	int iCheckForUpdates;
	int iLogLevel;
	int iFilenameFormat;
	TCHAR acTheme[64];
	TCHAR acVersion[16];
};

extern struct udtOptions gudtOptions;
extern bool gbProcess;
extern bool gbStop;

// ---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published: // IDE-managed Components

	TStringGrid *grdFiles;
	TPopupMenu *mnuFiles;
	TMenuItem *mnuFilesOptimize;
	TMenuItem *mnuFilesClear;
	TMenuItem *N1;
	TLabel *lblInstructions;
	TTimer *tmrMain;
	TStatusBar *stbMain;
	TProgressBar *pgbProgress;
	TMenuItem *mnuFilesRemove;
	TMenuItem *mnuFilesAdd;
	TMenuItem *N2;
	TMenuItem *mnuFilesOptions;
	TMenuItem *mnuFilesAbout;
	TMenuItem *mnuFilesExit;
	TMenuItem *mnuFilesHelp;
	TOpenDialog *dlgAddFiles;
	TRibbon *rbnMain;
	TRibbonPage *pagFile;
	TRibbonGroup *grpFile;
	TRibbonGroup *grpOptimize;
	TRibbonGroup *grpHelp;
	TActionManager *mgrMain;
	TAction *actAdd;
	TAction *actRemove;
	TAction *actClear;
	TAction *actOptimize;
	TAction *actOptions;
	TAction *actAbout;
	TAction *actInformation;
	TAction *actExit;
	TImageList *imgMain;
	TRibbonQuickAccessToolbar *rbnQuick;
	TRibbonApplicationMenuBar *rbnApplication;
	TAction *actDonate;
	TMenuItem *mnuFilesDonate;
	TMenuItem *N3;
	TAction *actStop;
	TMenuItem *mnuFilesStop;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall mnuFilesOptimizeClick(TObject *Sender);
	void __fastcall mnuFilesClearClick(TObject *Sender);
	void __fastcall lblCopyrightClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall tmrMainTimer(TObject *Sender);
	void __fastcall stbMainDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect);
	void __fastcall grdFilesDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall grdFilesFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall grdFilesMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall mnuFilesHelpClick(TObject *Sender);
	void __fastcall mnuFilesExitClick(TObject *Sender);
	void __fastcall mnuFilesAboutClick(TObject *Sender);
	void __fastcall mnuFilesOptionsClick(TObject *Sender);
	void __fastcall mnuFilesRemoveClick(TObject *Sender);
	void __fastcall mnuFilesAddClick(TObject *Sender);
	void __fastcall grdFilesDblClick(TObject *Sender);
	void __fastcall actAddExecute(TObject *Sender);
	void __fastcall actRemoveExecute(TObject *Sender);
	void __fastcall actClearExecute(TObject *Sender);
	void __fastcall actExitExecute(TObject *Sender);
	void __fastcall actOptimizeExecute(TObject *Sender);
	void __fastcall actOptionsExecute(TObject *Sender);
	void __fastcall actAboutExecute(TObject *Sender);
	void __fastcall actInformationExecute(TObject *Sender);
	void __fastcall rbnMainHelpButtonClick(TObject *Sender);
	void __fastcall actDonateExecute(TObject *Sender);
	void __fastcall actStopExecute(TObject *Sender);
	void __fastcall mnuFilesStopClick(TObject *Sender);
	void __fastcall mnuFilesDonateClick(TObject *Sender);





private: // User declarations
	BEGIN_MESSAGE_MAP
		// add message handler for WM_DROPFILES
		VCL_MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WMDropFiles)
	END_MESSAGE_MAP(TComponent)
	String __fastcall GetExtensionByContent (String psFilename);
	String __fastcall GetExtension (String psFilename);
	String __fastcall GetFilename (String psFilename);
	String __inline FormatNumberThousand (int piNumber);
	int __inline ParseNumberThousand (String psNumber);
	int __fastcall RunPluginOld(int piCurrent, String psStatus, String psProcess, String psDirectory, String psTmpName);
	int __fastcall RunPlugin(int piCurrent, String psStatus, String psCommandLine, String psDirectory, String psInputFile, String psOutputFile);
	unsigned long __fastcall RunProcess(const TCHAR *pacProcess, const TCHAR *pacDirectory, TCHAR *pacOutput, unsigned int piOutputLen, bool pbWait);
	void __fastcall WMDropFiles(TWMDropFiles &udtMessage);
	void __fastcall AddFiles(const TCHAR *pacFile);
	void __fastcall CheckForUpdates(bool pbSilent = true);
	String __fastcall GetShortName(String psLongName);
	bool __fastcall IsAPNG(const TCHAR *pacFile);
	bool __fastcall IsInnoSetup(const TCHAR *pacFile);
	bool __fastcall IsManagedNet(const TCHAR *pacFile);
	String __fastcall GetCellValue(String psValue, unsigned int piPos);
	String __fastcall SetCellFileValue(String psValue);

public: // User declarations
	__fastcall TfrmMain(TComponent* Owner);
	void __fastcall RefreshStatus(bool pbUpdateStatusBar = true, unsigned int piTotalBytes = 0, unsigned int piSavedBytes = 0);
	void __fastcall UpdateTheme(const TCHAR *pacTheme);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
// ---------------------------------------------------------------------------
#endif
