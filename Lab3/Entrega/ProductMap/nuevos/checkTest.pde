import controlP5.*;

ControlP5 myCP5;
PImage t1, t2;

void setup() {
  size(400, 400);

  myCP5 = new ControlP5(this);

  t1 = loadImage("CARNE-Y-DERIVADOS-OFF.png");
  t2 = loadImage("CARNE-Y-DERIVADOS-ON.png");

  CheckBox cb = myCP5.addCheckBox("theChkbox")
  .setPosition(30, 20)
  .setItemsPerRow(2)
  .setSpacingColumn(80)
  .setSpacingRow(30)
  .setSize(t1)
  .addItem("First item", 1)
  .addItem("Second item", 2)
  .addItem("Third item", 3)
  .addItem("Fourth item", 4)
  ;
  
  for(Toggle t:cb.getItems()) {
    // replace the default view for each checkbox toggle with our custom view 
    t.setView(new CheckBoxItemView());
  }
  
}

void draw() {
  background(200);
}

public void theChkbox(int n) {
}


class CheckBoxItemView implements ControllerView<Toggle> {
  public void display(PApplet p, Toggle t) {
    if(t.getState()) {
      p.image(t1,0,0);
    } else {
      p.image(t2,0,0);
    }
    fill(255);
    t.getCaptionLabel().draw(p, 0, 0, t);
  }
}
