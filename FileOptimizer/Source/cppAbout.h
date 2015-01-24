//---------------------------------------------------------------------------
#ifndef cppAboutH
#define cppAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TfrmAbout : public TForm
{
__published:	// IDE-managed Components
	TImage *imgAbout;
	TButton *butClose;
	TMemo *mmoLicense;
	TLabel *lblProduct;
	TLabel *lblCopyright;
	TLabel *lblDetail;
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
