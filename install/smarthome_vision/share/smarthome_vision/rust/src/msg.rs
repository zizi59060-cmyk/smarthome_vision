#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to smarthome_vision__msg__DetectedTarget

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectedTarget {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,


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
    pub corners_uv: Vec<f32>,

}



impl Default for DetectedTarget {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DetectedTarget::default())
  }
}

impl rosidl_runtime_rs::Message for DetectedTarget {
  type RmwMsg = super::msg::rmw::DetectedTarget;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        mode: msg.mode,
        tracking: msg.tracking,
        class_id: msg.class_id,
        score: msg.score,
        x: msg.x,
        y: msg.y,
        z: msg.z,
        corners_uv: msg.corners_uv.into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      mode: msg.mode,
      tracking: msg.tracking,
      class_id: msg.class_id,
      score: msg.score,
      x: msg.x,
      y: msg.y,
      z: msg.z,
        corners_uv: msg.corners_uv.as_slice().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      mode: msg.mode,
      tracking: msg.tracking,
      class_id: msg.class_id,
      score: msg.score,
      x: msg.x,
      y: msg.y,
      z: msg.z,
      corners_uv: msg.corners_uv
          .into_iter()
          .collect(),
    }
  }
}


