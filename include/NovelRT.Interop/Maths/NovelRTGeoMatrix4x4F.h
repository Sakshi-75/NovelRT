// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_H
#define NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_H

#include "NovelRTGeoVector4F.h"

#ifdef __cplusplus
extern "C" {
#endif

  struct NovelRTGeoMatrix4x4F
  {
    NovelRTGeoVector4F x;
    NovelRTGeoVector4F y;
    NovelRTGeoVector4F z;
    NovelRTGeoVector4F w;
  };

  int32_t NovelRT_GeoMatrix4x4F_isNaN(NovelRTGeoMatrix4x4F matrix);
  NovelRTGeoMatrix4x4F NovelRT_GeoMatrix4x4F_getDefaultIdentity();
  int32_t NovelRT_GeoMatrix4x4F_equal(NovelRTGeoMatrix4x4F lhs, NovelRTGeoMatrix4x4F rhs);
  int32_t NovelRT_GeoMatrix4x4F_notEqual(NovelRTGeoMatrix4x4F lhs, NovelRTGeoMatrix4x4F rhs);
  int32_t NovelRT_GeoMatrix4x4F_addMatrix(NovelRTGeoMatrix4x4F lhs, NovelRTGeoMatrix4x4F rhs, NovelRTGeoMatrix4x4F* result);
  int32_t NovelRT_GeoMatrix4x4F_subtractMatrix(NovelRTGeoMatrix4x4F lhs, NovelRTGeoMatrix4x4F rhs, NovelRTGeoMatrix4x4F* result);
  int32_t NovelRT_GeoMatrix4x4F_multiplyMatrix(NovelRTGeoMatrix4x4F lhs, NovelRTGeoMatrix4x4F rhs, NovelRTGeoMatrix4x4F* result);
  int32_t NovelRT_GeoMatrix4x4F_addAssignMatrix(NovelRTGeoMatrix4x4F* lhs, NovelRTGeoMatrix4x4F rhs);
  int32_t NovelRT_GeoMatrix4x4F_subtractAssignMatrix(NovelRTGeoMatrix4x4F* lhs, NovelRTGeoMatrix4x4F rhs);
  int32_t NovelRT_GeoMatrix4x4F_multiplyAssignMatrix(NovelRTGeoMatrix4x4F* lhs, NovelRTGeoMatrix4x4F rhs);
  int32_t NovelRT_GeoMatrix4x4F_addFloat(NovelRTGeoMatrix4x4F lhs, float rhs, NovelRTGeoMatrix4x4F* result);
  int32_t NovelRT_GeoMatrix4x4F_subtractFloat(NovelRTGeoMatrix4x4F lhs, float rhs, NovelRTGeoMatrix4x4F* result);
  int32_t NovelRT_GeoMatrix4x4F_multiplyFloat(NovelRTGeoMatrix4x4F lhs, float rhs, NovelRTGeoMatrix4x4F* result);
  int32_t NovelRT_GeoMatrix4x4F_addAssignFloat(NovelRTGeoMatrix4x4F* lhs, float rhs);
  int32_t NovelRT_GeoMatrix4x4F_subtractAssignFloat(NovelRTGeoMatrix4x4F* lhs, float rhs);
  int32_t NovelRT_GeoMatrix4x4F_multiplyAssignFloat(NovelRTGeoMatrix4x4F* lhs, float rhs);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_MATHS_GEOMATRIX4X4F_H
