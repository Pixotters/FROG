#ifndef MATCHINFO_HPP
#define MATCHINFO_HPP

typedef enum{
  KO, //each KO counts as 1 point 
  ROUND, //1 point for the one who makes more KO in this round
  DAMAGE //damages count as score
} MatchType;

struct MatchInfo
{
  MatchType type;
  unsigned short roundsNumber;
  unsigned short strengthModifier;
  unsigned short fatigueModifier;
  unsigned short timePerRound;
  bool TKO; // when 5 KOs in 1 round, the match ends
};

#endif
