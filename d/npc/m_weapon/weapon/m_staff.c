// m_sword.c

#include <ansi.h>
#include <weapon.h>

inherit M_WEAPON;


int duanlian(object weapon);
int do_hui(object weapon);


string query_autoload() { return 1 + ""; }	//autoload weapon

void init()
{
        add_action("do_duanlian","duanlian");
	add_action("do_hui","hui");
}


void create()
{	
	object me;
	string w_name,w_id,w_or;
	int w_lv;
	me = this_player();
//��������
	w_name=me->query("weapon/name");
	w_id = me->query("weapon/id");
	w_or = me->query("weapon/or");
	w_lv = me->query("weapon/lv");
	set_name(w_name, ({w_id}));
	set("unit", "��");   
	set("no_get",1);
	set("no_drop",1);
	set_desc(w_lv,w_or,w_name);
	switch(w_or)
		{
		case "ǧ����ľ" :
			set_weight(500);
			set("material", "iron");
			break;
		case "���׽�ĸ" :
			set_weight(1000);
			set("material", "steel");
			break;
		case "��˿����" :
			set_weight(30);
			set("material", "bamboo");
			break;
		default :
		} 
	set("wield_msg", "$N������һ�����ͳ���һ��"+w_name+"\n");
	set("unwield_msg", "$N����"+w_name+"һ�ӣ�գ�ۼ���Ȼ����Ӱ�١�\n");
	init_staff(w_lv * 10);
	setup();
}	



int do_duanlian(object weapon)
{
	object me;
	int w_zhi, w_level;
	string w_or;

	me=this_player();
	if( !weapon )
		return notify_fail("��Ҫ����ʲô?\n");

	if( (int)me->query("max_neili") < 10 )
		return notify_fail("��������������޷��������壡\n");

	if( (int)me->query("qi") < 150 )
		return notify_fail("������������޷��������壡\n");

	if( (int)me->query("eff_qi") < 30 )
		return notify_fail("�����ڵ�����̫�����޷��������壡\n");

	if( (int)me->query("eff_jing") < 10 )
		return notify_fail("�����ڵľ����޷����У����ܶ������壡\n");

	if( ((int)me->query("potential") - (int)me->query("learned_points"))< 2 )
		return notify_fail("���Ǳ�ܲ������޷��������壡\n");

	message_vision(HIR "$N�����ȶˣ�һ������˿˿�Ĵ��˽�ȥ��\n" NOR, me);

	me->add("max_neili",-10);
	me->set("neili", (int)me->query("max_neili"));
	me->add("qi",-150);
	me->add("eff_qi",-30);
	me->add("eff_jing",-30);
	me->add("learned_points", 2);

	w_zhi = (int)me->query("weapon/value");
	w_zhi++;
	me->set("weapon/value", w_zhi);
	w_or = (string)me->query("weapon/or");
	w_level = (int)me->query("weapon/lv");
	if( w_zhi >= ((w_level + 1) * (w_level + 1)))
	{
		w_level++;
		me->set("weapon/lv", w_level);
		message_vision(HIY "��������һ����һ���������$N�����壬�����ˣ�\n" NOR,me);
		message_vision(HIG "$N���ȵĵȼ�����ˣ�\n" NOR, me);
		weapon=this_object();
		if(weapon->query("equipped") ) 
			weapon->unequip();
		reload_object( weapon );
		me->set("weapon/value",0);
		return 1;
	}
	message_vision(RED "$N���ȵ�Ӳ�������!\n" NOR, me);
	return 1;
}


int do_hui(object weapon)
{	
	string w_name;
	object me,ob;
	me=this_player();
	w_name=me->query("weapon/name");
	if( !weapon )
		return notify_fail("��Ҫ�ݻ�ʲô?\n");
	message_vision(HIR "����һ����һ�����ȣ�һ���������¡������¡һ������"
			+w_name+"��Ϊ����!\n" NOR,me);
	me->set("weapon/make",0);
	destruct( this_object() );
	me->delete("weapon");
	
	me->save();

	return 1;
}