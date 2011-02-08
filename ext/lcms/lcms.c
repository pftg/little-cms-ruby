#include "ruby.h"
#include "lcms2.h"


static VALUE rb_mLCMS, rb_cLCMSTransform;


//static VALUE transform_mark(cmsHTRANSFORM hTransform){
//
//}
//
//static void transform_free(cmsHTRANSFORM hTransform){
//    if(hTransform)
//      cmsDeleteTransform(hTransform);
//}
//
//static VALUE transform_allocate(VALUE klass){
//    return Data_Wrap_Struct(klass, NULL, transform_free, NULL);
//}

static VALUE transform_init(VALUE self, VALUE in, VALUE out) {
  rb_iv_set(self, "@in", in);
  rb_iv_set(self, "@out", out);
  return self;
}


static VALUE transform_convert(int argc, VALUE *argv, VALUE self){

  if(argc != 4){
    return Qnil;
  }

  cmsHPROFILE hInProfile, hOutProfile;
  cmsHTRANSFORM hTransform;

  VALUE in = rb_iv_get(self, "@in");
  VALUE out = rb_iv_get(self, "@out");

  hInProfile = cmsOpenProfileFromFile(RSTRING(in)->ptr, "r");
  hOutProfile = cmsOpenProfileFromFile(RSTRING(out)->ptr, "r");

  hTransform = cmsCreateTransform(hInProfile, TYPE_CMYK_8,
      hOutProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);

  cmsCloseProfile(hInProfile);
  cmsCloseProfile(hOutProfile);


  //TODO: Remove duplication
  cmsUInt8Number cmyk_temp[4] = { NUM2INT(argv[0]), NUM2INT(argv[1]), NUM2INT(argv[2]), NUM2INT(argv[3]) };;
  cmsUInt8Number rgb_temp[3];

//  printf("Transfrom result is cmyk(%d, %d, %d, %d)\n", cmyk_temp[0], cmyk_temp[1], cmyk_temp[2], cmyk_temp[3]);

  cmsDoTransform(hTransform, cmyk_temp, rgb_temp, 1);


//  printf("Transfrom result is rgb(%d, %d, %d)\n", rgb_temp[0], rgb_temp[1], rgb_temp[2]);

  return rb_ary_new3(3, INT2FIX(rgb_temp[0]), INT2FIX(rgb_temp[1]), INT2FIX(rgb_temp[2]));
}

void Init_lcms() {
  rb_mLCMS = rb_define_module ("LCMS");
  rb_cLCMSTransform = rb_define_class_under (rb_mLCMS, "Transform", rb_cObject);
//  rb_define_alloc_func (rb_cLCMSTransform, transform_allocate);
  rb_define_method(rb_cLCMSTransform, "initialize", transform_init, 2);
  rb_define_method(rb_cLCMSTransform, "convert", transform_convert, -1);
}





int main(void) {
  cmsHPROFILE hInProfile, hOutProfile;
  cmsHTRANSFORM hTransform; 
  int i;
  
  hInProfile = cmsOpenProfileFromFile("USWebCoatedSWOP.icc", "r");
  hOutProfile = cmsOpenProfileFromFile("AdobeRGB1998.icc", "r");
  
  hTransform = cmsCreateTransform(hInProfile, TYPE_CMYK_8,
      hOutProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
  
  cmsCloseProfile(hInProfile);
  cmsCloseProfile(hOutProfile);



  return 0;
}
