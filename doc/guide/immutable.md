# Immutable

## 모든 타입은 기본적으로 mutable이다.

## 빌트인 타입의 일부만 immutable이다.

* int, float, bool, byte 

## immutable여부는 native의 type이 가진다.

## immutable일 경우 refer의 동작만 변하면 된다.

## 파서는 ast분석시 immutable인 member에 대해서는 refer로 감싸지 않는다.

## immutable도 refer가 가리킬 수 있다.
