//---------------------------------------------------------------------------
#pragma once
#ifndef cppOptionsH
#define cppOptionsH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Samples.Spin.hpp>
//---------------------------------------------------------------------------
class TfrmOptions : public TForm
{
__published: // IDE-managed Components
	TPageControl *tabOptions;
	TTabSheet *pagGeneral;
	TTabSheet *pagCSS;
	TTabSheet *pagEXE;
	TTabSheet *pagGIF;
	TTabSheet *pagGZ;
	TTabSheet *pagHTML;
	TTabSheet *pagJPEG;
	TTabSheet *pagJS;
	TTabSheet *pagLUA;
	TTabSheet *pagMP3;
	TTabSheet *pagPNG;
	TTabSheet *pagPDF;
	TTabSheet *pagXML;
	TTabSheet *pagZIP;
	TLabel *lblOptimizationLevel;
	TComboBox *cboOptimizationLevel;
	TLabel *lblProcessPriority;
	TComboBox *cboProcessPriority;
	TLabel *lblCheckForUpdates;
	TComboBox *cboCheckForUpdates;
	TComboBox *cboTheme;
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
	TLabel *lblTheme;
	TCheckBox *chkGIFCopyMetadata;
	TCheckBox *chkGIFAllowLossy;	
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall butCancelClick(TObject *Sender);
	void __fastcall butOKClick(TObject *Sender);
	void __fastcall chkCSSEnableTidyClick(TObject *Sender);
	void __fastcall butRestoreDefaultsClick(TObject *Sender);
	void __fastcall cboPDFProfileChange(TObject *Sender);
private: // User declarations
public: // User declarations
	__fastcall TfrmOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
//---------------------------------------------------------------------------
#endif