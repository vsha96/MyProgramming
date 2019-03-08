Unit Unit1;

interface

uses System, System.Drawing, System.Windows.Forms;

type
  Form1 = class(Form)
    procedure label1_Click(sender: Object; e: EventArgs);
  {$region FormDesigner}
  private
    {$resource Unit1.Form1.resources}
    label2: &Label;
    label3: &Label;
    label4: &Label;
    label5: &Label;
    textBox1: TextBox;
    textBox2: TextBox;
    button1: Button;
    label1: &Label;
    {$include Unit1.Form1.inc}
  {$endregion FormDesigner}
  public
    constructor;
    begin
      InitializeComponent;
    end;
  end;

implementation

procedure Form1.label1_Click(sender: Object; e: EventArgs);
begin
  
end;

end.
