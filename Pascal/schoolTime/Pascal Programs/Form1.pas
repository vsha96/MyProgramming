Unit Unit1;

interface

uses System, System.Drawing, System.Windows.Forms;

type
  Form1 = class(Form)
    procedure label2_Click(sender: Object; e: EventArgs);
  {$region FormDesigner}
  private
    {$resource Unit1.Form1.resources}
    label1: &Label;
    label2: &Label;
    label4: &Label;
    label5: &Label;
    button1: Button;
    textBox1: TextBox;
    textBox2: TextBox;
    label3: &Label;
    {$include Unit1.Form1.inc}
  {$endregion FormDesigner}
  public
    constructor;
    begin
      InitializeComponent;
    end;
  end;

implementation

procedure Form1.label2_Click(sender: Object; e: EventArgs);
begin
  
end;

end.
