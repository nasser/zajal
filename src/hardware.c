#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global hardware module */
VALUE zj_mHardware;

VALUE zj_cArduino;
VALUE zj_cSerial;

void zj_arduino_dealloc(void* arduino) {
  ((ofArduino*)arduino)->disconnect();
  delete (ofArduino*)arduino;
}

VALUE zj_arduino_new(int argc, VALUE* argv, VALUE klass) {
  ofArduino* arduino_ptr = new ofArduino();
  
  VALUE arduino = Data_Wrap_Struct(klass, 0, zj_arduino_dealloc, arduino_ptr);
  rb_obj_call_init(arduino, argc, argv);
  return arduino;
}

VALUE zj_arduino_initialize(int argc, VALUE* argv, VALUE self) {
  VALUE device = Qnil, baud = Qnil;
  VALUE connect = Qtrue;
  bool hash_given = (argc > 0 && TYPE(argv[argc-1]) == T_HASH);
  
  /* scan for normal args, ignore hash if given */
  rb_scan_args(hash_given ? argc-1 : argc, argv, "02", &device, &baud);
  
  /* if last arg is options hash, extract local variables */
  if(hash_given) {
    HASH_EXTRACT(argv[argc-1], device);
    HASH_EXTRACT(argv[argc-1], baud);
    HASH_EXTRACT(argv[argc-1], connect);
  }
  
  /* TODO support no device */
  // if(NIL_P(device)) device = firstAvailableArduino();
  if(NIL_P(baud)) baud = INT2FIX(9600);
  
  rb_iv_set(self, "@device", device);
  rb_iv_set(self, "@baud", baud);
  
  /* TODO remove me */
  rb_iv_set(self, "@did_setup", Qfalse);
  
  /* connect right away unless user set connect: false hash key */
  if(RTEST(connect)) rb_funcall(self, rb_intern("connect"), 0);
  
  return self;
}

/* 
 * Connect to the Arduino
 */
VALUE zj_arduino_connect(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  VALUE device = rb_iv_get(self, "@device");
  VALUE baud = rb_iv_get(self, "@baud");
  
  arduino_ptr->connect(RSTRING_PTR(device), FIX2INT(baud));
  
  return Qnil;
}

/* 
 * Disconnect from the Arduino
 * 
 * @todo This should be managed internally on exit
 */
VALUE zj_arduino_disconnect(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  arduino_ptr->disconnect();
  
  return Qnil;
}

/* 
 * Update the Arduino
 * 
 * @todo This should be managed internally on update
 */
VALUE zj_arduino_update(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  arduino_ptr->update();
  
  return Qnil;
}

/* 
 * Is the Arduino initialized?
 * 
 * @todo Whats the difference between this and #ready? ?
 */
VALUE zj_arduino_initialized_p(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  return arduino_ptr->isInitialized() ? Qtrue : Qfalse;
}

/* 
 * Is the Arduino ready?
 * 
 * @return [Boolean]
 */
VALUE zj_arduino_ready_p(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  return arduino_ptr->isArduinoReady() ? Qtrue : Qfalse;
}

/* 
 * Get firmware name
 */
VALUE zj_arduino_firmware(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  return rb_str_new2(arduino_ptr->getFirmwareName().c_str());
}

VALUE zj_arduino_digital(VALUE self, VALUE pin, VALUE val) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  arduino_ptr->sendDigital(NUM2INT(pin), NUM2INT(val), true);
  
  return Qnil;
}

VALUE zj_arduino_setup(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  if(!RTEST(rb_iv_get(self, "@did_setup")) && arduino_ptr->isArduinoReady()) {
    rb_iv_set(self, "@did_setup", Qtrue);
    
    for (int i = 0; i < 13; i++){
  		arduino_ptr->sendDigitalPinMode(i, ARD_OUTPUT);
  	}

  	arduino_ptr->sendDigitalPinMode(13, ARD_OUTPUT);
  	arduino_ptr->sendAnalogPinReporting(0, ARD_ANALOG);
  	arduino_ptr->sendDigitalPinMode(11, ARD_PWM);
  }
}


void Init_Hardware() {
  zj_mHardware = rb_define_module_under(zj_mZajal, "Hardware");
  rb_define_module_under(zj_mHardware, "Internals");
  
  zj_cArduino = rb_define_class_under(zj_mHardware, "Arduino", rb_cObject);
  rb_define_singleton_method(zj_cArduino, "new", RUBY_METHOD_FUNC(zj_arduino_new), -1);
  rb_define_method(zj_cArduino, "initialize", RUBY_METHOD_FUNC(zj_arduino_initialize), -1);
  rb_define_method(zj_cArduino, "connect", RUBY_METHOD_FUNC(zj_arduino_connect), 0);
  rb_define_method(zj_cArduino, "disconnect", RUBY_METHOD_FUNC(zj_arduino_disconnect), 0);
  rb_define_method(zj_cArduino, "update", RUBY_METHOD_FUNC(zj_arduino_update), 0);
  rb_define_method(zj_cArduino, "initialized", RUBY_METHOD_FUNC(zj_arduino_initialized_p), 0);
  rb_define_method(zj_cArduino, "ready?", RUBY_METHOD_FUNC(zj_arduino_ready_p), 0);
  rb_define_method(zj_cArduino, "firmware", RUBY_METHOD_FUNC(zj_arduino_firmware), 0);
  
  /* TODO remove me */
  rb_define_method(zj_cArduino, "setup", RUBY_METHOD_FUNC(zj_arduino_setup), 0);
  
  rb_define_method(zj_cArduino, "digital", RUBY_METHOD_FUNC(zj_arduino_digital), 2);
  
  zj_cSerial = rb_define_class_under(zj_mHardware, "Serial", rb_cObject);
  
}