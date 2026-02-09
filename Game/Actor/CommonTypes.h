#pragma once

// #define보다 const, enum, inline을 우선하자
enum class ParryingQuality
{
    Perfect,   // 0 ~ 0.2s
    Great,    // 0.2s ~ 0.5s
    Guard,     // 0.5s ~ 1.0s
	Fail	// 임시.
};

struct HitResult {
    ParryingQuality parryingQuality;  // 패링퀄리티
    int damage;                     // 체력 데미지
    int postureDamage;              //체간 데미지
};

//enum class AttackType 
//{
//    // 일반 공격
//    Normal
//};
//
//struct AttackInfo {
//    const Combatant* attacker; // 누가 때렸는지
//    int damage;           // 체력 데미지
//    int postureDamage;       // 체간 데미지
//    AttackType type;            // 공격 속성
//    // ... 위치, 넉백 방향 등 추가 가능
//};