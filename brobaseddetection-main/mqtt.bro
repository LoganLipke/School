export {
  redef enum Notice::Type += {
    ## Generated when a mqtt packet is seen subscribing to the topic of '#'
    Mqtt::Subscribe,
  };
}

function parse_payload(c: connection, payload: string)
{
  local state = 0;
  local index = 0;
  for (letter in payload)
  {
    index += 1;
    local dist = 0;
    if (state == 1)
    {
      dist = bytestring_to_count(letter);
      if (payload[index + dist - 2] == "#")
          NOTICE([$note=Mqtt::Subscribe, $msg=fmt("%s attempts to subscribe to SUB/# topics.", c$id$orig_h)]);
    }

    if (letter == "\x82")
      state = 1;
    else
      state = 0;

  }

}

event tcp_packet(c: connection, is_orig: bool, flags: string, seq: count, ack: count, len: count, payload: string)
{
  if ("\x82" in payload && "#" in payload)
  {
    parse_payload(c, payload);
    # NOTICE([$note=Mqtt::Subscribe, $msg=fmt("%s attempts to subscribe to SUB/# topics.", c$id$orig_h)]);
    # print payload;
    # print c$id$orig_h;
  }
}
