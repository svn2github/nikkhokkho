//---------------------------------------------------------------------------
#pragma once
#ifndef cppOptionsH
#define cppOptionsH
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.StdCtrls.hpp>
#include "FileOptimizerPCH1.h"
#include "cppMain.h"
#include "clsUtil.h"
#include "clsLanguage.h"


//---------------------------------------------------------------------------
class TfrmOptions : public TForm
{
__published: // IDE-managed Components
	TPageControl *tabOptions;
	TTabSheet *pagGeneral1;
	TTabSheet *pagBMP;
	TTabSheet *pagCSS;
	TTabSheet *pagEXE;
	TTabSheet *pagGIF;
	TTabSheet *pagGZ;
	TTabSheet *pagHTML;
	TTabSheet *pagJPEG;
	TTabSheet *pagJS;
	TTabSheet *pagLUA;
	TTabSheet *pagMisc;
	TTabSheet *pagMP3;
	TTabSheet *pagMP4;
	TTabSheet *pagPCX;
	TTabSheet *pagPNG;
	TTabSheet *pagPDF;
	TTabSheet *pagTGA;
	TTabSheet *pagTIFF;
	TTabSheet *pagXML;
	TTabSheet *pagZIP;
	TLabel *lblOptimizationLevel;
	TComboBox *cboOptimizationLevel;
	TLabel *lblProcessPriority;
	TComboBox *cboProcessPriority;
	TLabel *lblCheckForUpdates;
	TComboBox *cboCheckForUpdates;
	TLabel *lblLogLevel;
	TComboBox *cboLogLevel;
	TCheckBox *chkKeepAttributes;
	TCheckBox *chkDoNotUseRecycleBin;	
	TLabel *lblExcludeMask;
	TEdit *txtExcludeMask;
	TCheckBox *chkCSSEnableTidy;
	TLabel *lblCSSTemplate;
	TComboBox *cboCSSTemplate;
	TCheckBox *chkEXEDisablePETrim;
	TCheckBox *chkEXEEnableUPX;
	TCheckBox *chkGZCopyMetadata;
	TCheckBox *chkHTMLEnableTidy;
	TCheckBox *chkJPEGCopyMetadata;
	TCheckBox *chkJPEGUseArithmeticEncoding;
	TCheckBox *chkJPEGAllowLossy;
	TCheckBox *chkJSEnableJSMin;
	TCheckBox *chkLUAEnableLeanify;
	TCheckBox *chkMP3CopyMetadata;
	TLabel *lblPDFProfile;
	TComboBox *cboPDFProfile;
	TCheckBox *chkPNGCopyMetadata;
	TCheckBox *chkPNGAllowLossy;
	TCheckBox *chkXMLEnableLeanify;
	TCheckBox *chkZIPCopyMetadata;
	TCheckBox *chkZIPRecurse;
	TButton *butOK;
	TButton *butCancel;
	TButton *butRestoreDefaults;
	TShape *shpDialogBackground;
	TLabel *lblTitle;
	TImage *imgDialogPicture;
	TShape *shpDialogLineG1;
	TLabel *lblDescription;
	TSpinEdit *spnPDFCustomDPI;
	TLabel *lblPDFCustomDPI;
	TTabSheet *pagAppearance;
	TCheckBox *chkGIFCopyMetadata;
	TCheckBox *chkGIFAllowLossy;
	TEdit *txtDonator;
	TLabel *lblDonator;
	TCheckBox *chkShowToolBar;
	TLabel *lblIncludeMask;
	TEdit *txtIncludeMask;
	TCheckBox *chkBMPCopyMetadata;
	TCheckBox *chkMiscCopyMetadata;
	TCheckBox *chkMP4CopyMetadata;
	TCheckBox *chkPCXCopyMetadata;
	TCheckBox *chkTGACopyMetadata;
	TCheckBox *chkTIFFCopyMetadata;
	TTabSheet *pagGeneral2;
	TLabel *lblDisablePluginMask;
	TEdit *txtDisablePluginMask;
	TCheckBox *chkBeepWhenDone;
	TCheckBox *chkShutdownWhenDone;
	TCheckBox *chkClearWhenComplete;
	TCheckBox *chkAlwaysOnTop;
	TCheckBox *chkPDFSkipLayered;
	TCheckBox *chkAllowDuplicates;
	TCheckBox *chkAllowMultipleInstances;
	TLabel *lblJSAdditionalExtensions;
	TEdit *txtJSAdditionalExtensions;
	TLabel *lblTempDirectory;
	TEdit *txtTempDirectory;
	TLabel *lblLeanifyIterations;
	TSpinEdit *spnLeanifyIterations;
	TCheckBox *chkEnableCache;
	TLabel *lblFilenameFormat;
	TComboBox *cboFilenameFormat;
	TCheckBox *chkHideAds;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall butCancelClick(TObject *Sender);
	void __fastcall butOKClick(TObject *Sender);
	void __fastcall chkCSSEnableTidyClick(TObject *Sender);
	void __fastcall butRestoreDefaultsClick(TObject *Sender);
	void __fastcall cboPDFProfileChange(TObject *Sender);
private: // User declarations
public: // User declarations
	__fastcall TfrmOptions(TComponent* Owner);
    __fastcall ~TfrmOptions();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
//---------------------------------------------------------------------------
#endif