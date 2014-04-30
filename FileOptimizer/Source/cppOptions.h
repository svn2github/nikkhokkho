//---------------------------------------------------------------------------

#ifndef cppOptionsH
#define cppOptionsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmOptions : public TForm
{
__published: // IDE-managed Components
	TPageControl *tabOptions;
	TTabSheet *pagGeneral;
	TTabSheet *pagCSS;
	TTabSheet *pagEXE;
	TTabSheet *pagGZ;
	TTabSheet *pagHTML;
	TTabSheet *pagJPEG;
	TTabSheet *pagJS;	
	TTabSheet *pagPNG;
	TTabSheet *pagPDF;
	TTabSheet *pagZIP;
	TLabel *lblOptimizationLevel;
	TComboBox *cboOptimizationLevel;
	TLabel *lblProcessPriority;
	TComboBox *cboProcessPriority;
	TLabel *lblCheckForUpdates;
	TComboBox *cboCheckForUpdates;
	TLabel *lblTheme;
	TComboBox *cboTheme;
	TLabel *lblLogLevel;
	TComboBox *cboLogLevel;
	TCheckBox *chkKeepAttributes;
	TCheckBox *chkCSSEnableTidy;
	TCheckBox *chkEXEDisablePETrim;
	TCheckBox *chkGZCopyMetadata;
	TCheckBox *chkHTMLEnableTidy;
	TCheckBox *chkJPEGCopyMetadata;
	TCheckBox *chkJPEGUseArithmeticEncoding;
	TCheckBox *chkJSEnableJSMin;
	TCheckBox *chkMP3CopyMetadata;
	TLabel *lblPDFProfile;
	TComboBox *cboPDFProfile;
	TCheckBox *chkPNGCopyMetadata;
	TCheckBox *chkZIPCopyMetadata;
	TButton *butOK;
	TButton *butCancel;
	TButton *butRestoreDefaults;
	

	TShape *shpDialogBackground;
	TLabel *lblTitle;
	TImage *imgDialogPicture;
	TShape *shpDialogLineG1;
	TLabel *lblDescription;
	TCheckBox *chkDoNotUseRecycleBin;
	TLabel *lblCSSTemplate;
	TComboBox *cboCSSTemplate;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall butCancelClick(TObject *Sender);
	void __fastcall butOKClick(TObject *Sender);
	void __fastcall chkCSSEnableTidyClick(TObject *Sender);
private: // User declarations
public: // User declarations
	__fastcall TfrmOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
//---------------------------------------------------------------------------
#endif
