n,k = map(int,input().split())
if n==k:
	print("1")
	quit()
if k==1:
	print("Poor E.S.!")
	quit()
if k==2:
	print(2**(n-2))
	quit()
now=k
x=1
y=0
while x+y<=k:
	q,r = divmod(k,x+y+1)
	if r<=x:
		now+=q
		x=x+1-r
		y+=r
	else:
		now+=q+1
		x,y=2*x+y+1-r,r-x
	if now>=n:
		print(x+y)
		quit()
if n>=70711 and k==3:
	x=16941591005272801730840405905815469525858644993669700523195114168850502949632828945111570039080364605087077769185519536480804222065982674510386846433109347769202043777907848832568884380701786761189961112503159225360875062505682498546376565896352329677196013802022363476289376892492274595389204216191446781681221514168940050716444923219525852149555742001426809721599344540718410858218517179027954918388996998682138037653523638059789353341367980269322455845898680641683862221124543282338191695997287012672001164389643826500602474295246876748378065679141189025752700458410767503402690798781697197191422518329172568905178624568258164997873806883299007467654679084809278750809654180843527665490967230736646636094684263380714680849925976281169382534644536071522819573272946549036669615496810746260661237942576530229641942034788934276155125003067666746127960995235434387840673777259400253853948821654369608982039365082438675577475152151990373096705558531850586624804422791325692551821008551711907352631543133104777094304504736720475572327468573971822352492457692490337080402939746020896282504820796274646981139691954930294372115188300694104378264363475752247991903069210465413175707869025371957602935832095295017649966797128916161287633049733664551399999143239770452734837469569982544598837738881618235754524895301248979282982615257284520157765322433574241370706582657363888004465044663881046840084515184645529255824658024126918965654145895105517998141859380725264009025201303299665684266761034315819040903979698471750457129179102074722694285836970099827791047675150485372231963105768002730938368658884040386454901495457430340672410801622199264782272644552228586911346700998404567007531614978330470609468890896253008170226660697990392249590352318649664827262523780418608695765277340002239923180774800973723440953501719141139503334960672694766013268535551948053029756889231897587222759085950350273198324060938761374171209909690644286568222453094053372823966107267689539854309092106145232166720263658348141299736631909473402536780038829701013726455209509828089973839399591687073053866193154421466427856839558552962417995529141921817883807271170304980290869643102540838278402915968067547779024492644723721035252746679668407958436713503745429253512280927471574262044511479937480592923040853419745647346637505645777973050814743848291892547839244881135250512398112807974988504731601910989313350400423648638159782109764781291048503602183169311606145588469804539009734319917165339022878798351772223482128990965335540295580231744236073365886053953276147923569023818160658761534113519497955153907093145883517443874203028231331029494852675632834755507783204564404218933436329074431231883955747580056913810585591884673018335097273706756217886419548515273422446501921270122959708838175835834242307781461306839539005489323579154916192890150581829605048697719929529168004721404573824625196009827430486777792388042042595016441068299200607179687923838085188709363373286309835259608822865118122963142193007094000636222361553519599795552005753278967312697307259633719717820380908913079385323617505418404793745294633466286239484666857239968418508473787866771480007894536481406422761030130421842413661631259667432714558508119082133394788933788878869588070720828892234920415842489560321554479736690137213225186143151655530221571068386588951058052806939994590426213907037579890819664617724296411141483436232571147334595749674950309845389086687226483084681636071530746329374134177904066423790854961736166056411265420436518076394487980636523622058539428621464424272584812497057467804330248577823676732188511013190719958879678438427273347498661843488125686447348348294323973322443205525447773450891391337725898626386402036057116739291500552218276585154811794732967142119387240421390541930971461426021184255685220988973147821450470268032671253452616224760383367651774318999437277092144160635304428596165727010335747139540054371481698813511074845640495055997460789041113317459117802140874454652448809892473397523835628873067182701107806449595114788352045551202111950809037138271370147533846967567463828310320847562496559660568923459972322064875044805000685441962276632193750902046542149288963533559437285939801714798761788377939646018134216841508216925408059223580695554448040943084564867739277696742344201152776051255540413340417973504724431844785980339065031178578279290748851707923493651006287988639951553756682453021515061329555516796338261818261553728558235494393357685804091396722554450917063583476838209619157831116805555149539545808317040732918703448487594813471695972256916531250074462706681240258798173676207051523433956221647887594074582042285022648857631803813168844701905921150997690791212862663730127720664254224458867913388906268898113174252718333398560909768368451330641974938832053820951880673460520945436332471223655602743522169812797421677407491306975435366496947278556750611997254959877352837066358530685019240003773239840358737892821641542083088990406084003061826316758554762436497854330413550963730178696206017416816410813747771076203518291092680722118304913992962707635019448388685702121012031211626413936844343756671530965698866937999222797569052450115730215355734906993303665118807959270972434636518642416357870141090978192133472448394144858557340587981499612573427618466032243162720183534860404322239511914135776296036753723858939635210267186063459393930008415978356444955832246259790679122565912753859838828850237510391724273239109196406887744847324488210962236661017917826952500508491617211211902385687371351269065498464976889819835119182140272541371351838544813142024232935020195921471026985679250173326367679692881901446895813618030211748524815418302774649978809293041726165082603456079202013741238335672741736544499540964269773988285203334759923192043379025726452104406999650433159879813868977895728042272811016848263991981896158091082809912506514740892596879335902979436901474278125368720952313424200865937051618253182372419126883085478911343228136762369212804345499746353331063383913196653100373605460988412904899214856035632658294783527926555436276099438801542913048500015246033916798146112928414372005464040642670923297978583318717383969286455338276859456541252303775899519760216832232805741446187370131593107053917684944744248968712665668823305774611377833977497608373842522082626611682308296774743505979371951530641463925349918561005564593898453495223366586370784063108950200070492057728730617000409479339715200276897200135220944910396994226254000547585665471053435803814243080541601754053996497726230104055566999547862211525218544253262583824458020684147835864883339217214977475412458345982199522115479261616662733742136401843495344707564434682353974972152646800510354556242247596915280690469727815424619689122869795493617874630691060430007622488003388887899359820336830001297814597462107274879943300468267122912637372830365879446175118519615857284481660371663505691037087621890809368780176813515228378896234205575564879477965797691374934221417645888985942882194295398741533980203519165176226126178315285988599590087147196242804278001254551599928904871228445855515134577115406332584311639436137625192399892286330783754537927513851716771280393493708322821600985043019218853852363493519046309609722907130396630252227272199722762588814290174046076726539295590468066512836439184333103160519163514058405832427583537025136171411013767466879523821216291513196828556396992415832540363962722389736042201144261462314938318061776134751715863789526555656582628108758250628937394449363197403984375039177079293116486079258328238893537527007983642469074354082015969896848711417528720278828743286605561279842835056462335367875339037519238396275978017201853461508836481142224038023185080159757530527677813757790464503681786301701022256217438972042032371520035445750658320031435690683924908393497600739359256409432419747998558960957137931479620217534175141223958971272029759848919068610963030955740375101658774026592653687839638934081058953906661795628292288536069906733814298777933412139392652500672295146320080764270298974751824402259718957531661107542864659997236150066272712240614933564342658486948805454020758029187799061723003269546306879153773694046509638867025777732088678874295039077564940066784846247521777367891769501680129596290377254158835473591153324250517653000668862846966298230912754721521863374122639770320351293518481466993832318073976200857609368827393479618352338955836317652135386479682769133095362620883040549075961727751418484297566535855775590709256964538680088736935042421985693803339954982689105002803137958431068083289748909732924285061215360227801946599497044811323711646060642581413275404476179709739161690649499141702415490075721849151651693916975767971029403527582236127996176558267017757950666010513675677462332858610036127390933145115686385109014634191879216353604961372214889214608646206494139632440889159289988167725245519826182389380651203609272952804624795876549208685244289281244004311834649380072079840140892626655638842671668966249331660468481638033063511716599693497254759764541938654041710955306201246859674225670767996315264330337758149122588231961981505074686182672919456560713243945545793072937592234221714516435760441383983922884428609515833766395500281278758678226985661632601145038824967787249808109585165196274908973166717008972912051220127683827334145040145572814829118684746950909915362193825544584118977963999647744840353458540559465284780923028365463474408199103626786744359576492322743083215926060137820499069957969823122248330822033816690100331239451968265615147853898479262280819435640711306695667362385195397851759253436660857320367019173567809257309372198427948806339969860364861094707582516291478807269430796599316852550427654514657388073469172080631562605700785788886621786180851876412848469294049944856519880256266211711147689514949327486532274905068590729020674795088665377552135339477423696051653148443439081568046272470198704660494066532723784603158295008787417213438636418346714132571420580891586899097635661880521339138895788708894342859257582030872377134238146283464282444655822713129121643395604398367145441185629974664377340678132681701829637608988191869036278396114570575152820413016034683023773454195998054862829400977670581863654081700109256065492888196651875359643244666788444960506016840527865768191235140652435576706119042325156055001840500019489354544001722045538517529676238863111715186612083062267636508231545492375134488908432911195353270326554824017061289039651615839426979252183099318432192884372648557324452918609478848568524347078343569815817476157725151040363020607346548482815118738642928242389111276744637456544010346704703463301642702200073620579351663503294653833516173026259530276730624320224555062366903826231191859603469156869190048708708590301356324829559141982121795813571406972313390220983866633245236884347719921492563555147479182711280391873381995165572023100546691748787227731036747253015102853261168920556529565442172333303864610837816560512699797027985048478035009888740533801470979167568004023339843945341791833772557742304109695472756331295534559365197206842170330511928101677720393682484420268777950322661552430096047940447798025410298899693691461095435064260767191967464182265142407160428007204145316169049174261464350897467660032962683853208665238275731791785414919388241474722787154226178823176826328267337301485772991570735717379628197735538608211101533766990175035750457032940047736681134030580738487099718322879596387724586291597589972812041817237111169792143164547501693616107665358968169082347760219086654304620102780899913523610510953887699520586933128494427741802168152228190289896603429984065344791007741784072589006194654588817285209533691116848481732048486941241663064065747121266212663151091531543688715584712001975729582060856691105524028412989488112089790777927876133032523377107438589179346322325379776542375709771051638929483676726683650297099924773085365798672682483643808908899895087062171721711783333267416603725083841748159690254928724959295481240271125336378919347953610655499697623376866852761132751357033995875346247258358512654361877111855471775793073979239239846966429469910305090079423142346776618526095502618880844645384516101735578377662630729282322980018631890579071237940993104462769330679925251048044379513896179920156930534282422125996732214283845096879785582347740833706200038722460718836487835203411847971314161339093115126814075031405633925701500272098357166993340695532223775720066036445126650787441887484391969573647534063369
	y=1
	now=70711
while now<n:
	q,r = divmod(x,k-1)
	now+=1
	if r==0:
		x,y=y+q*k,0
	else:
		x,y=y+q*k+r+1,k-r-1
print(x+y)
