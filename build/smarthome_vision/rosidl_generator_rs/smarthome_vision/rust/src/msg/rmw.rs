#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "smarthome_vision__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__smarthome_vision__msg__DetectedTarget() -> *const std::ffi::c_void;
}

#[link(name = "smarthome_vision__rosidl_generator_c")]
extern "C" {
    fn smarthome_vision__msg__DetectedTarget__init(msg: *mut DetectedTarget) -> bool;
    fn smarthome_vision__msg__DetectedTarget__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DetectedTarget>, size: usize) -> bool;
    fn smarthome_vision__msg__DetectedTarget__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DetectedTarget>);
    fn smarthome_vision__msg__DetectedTarget__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DetectedTarget>, out_seq: *mut rosidl_runtime_rs::Sequence<DetectedTarget>) -> bool;
}

// Corresponds to smarthome_vision__msg__DetectedTarget
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectedTarget {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tracking: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub class_id: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub score: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub corners_uv: rosidl_runtime_rs::Sequence<f32>,

}



impl Default for DetectedTarget {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !smarthome_vision__msg__DetectedTarget__init(&mut msg as *mut _) {
        panic!("Call to smarthome_vision__msg__DetectedTarget__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DetectedTarget {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { smarthome_vision__msg__DetectedTarget__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { smarthome_vision__msg__DetectedTarget__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { smarthome_vision__msg__DetectedTarget__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DetectedTarget {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DetectedTarget where Self: Sized {
  const TYPE_NAME: &'static str = "smarthome_vision/msg/DetectedTarget";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__smarthome_vision__msg__DetectedTarget() }
  }
}


