//---------------------------------------------------------------------------
#ifndef cppAboutH
#define cppAboutH
//---------------------------------------------------------------------------
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Classes.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TfrmAbout : public TForm
{
__published:	// IDE-managed Components
	TImage *imgAbout;
	TButton *butClose;
	TLabel *lblProduct;
	TLabel *lblCopyright;
	TLabel *lblDetail;
	TMemo *mmoLicense;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall butCloseClick(TObject *Sender);
	void __fastcall lblCopyrightClick(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
	int __fastcall GetFileVersionField(const TCHAR *fn, const TCHAR *info, TCHAR *ret, int len);
public:		// User declarations
	__fastcall TfrmAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
#endif
