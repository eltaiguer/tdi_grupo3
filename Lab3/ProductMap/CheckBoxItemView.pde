    class CheckBoxItemView implements ControllerView<Toggle> {
    public void display(PApplet p, Toggle t) {
      if(t.getState()) {
        p.image(img_capitulos_checked.get((int)t.internalValue()),0,0);
      } else {
        p.image(img_capitulos.get((int)t.internalValue()),0,0);
      }
      fill(255);
      t.getCaptionLabel().draw(p, 0, 0, t);
    }
  }
